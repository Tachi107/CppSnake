#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <utility>
#include <unordered_map>
#include <glad/glad.h>

class Shader {
	GLuint id;
	mutable std::unordered_map<std::string, GLint> uniformLocationCache;
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath) {
	    auto[vertexShader, fragmentShader] = parseShaders(vertexPath.c_str(), fragmentPath.c_str());
	    id = createShader(vertexShader, fragmentShader);
	}

    Shader(const char* const vertexPath, const char* const fragmentPath) {
        auto[vertexShader, fragmentShader] = parseShaders(vertexPath, fragmentPath);
        id = createShader(vertexShader, fragmentShader);
    }

	~Shader() {
        glDeleteProgram(id);
    }

	void bind() const {
        glUseProgram(id);
    }

	void unbind() const {
        glUseProgram(0);
	}

    void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
        glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
    }

private:
    static std::pair<std::string, std::string> parseShaders(const char* const vertexPath, const char* const fragmentPath) {
        enum ShaderType {
            VERTEX = 0, FRAGMENT = 1
        };
        std::ifstream vertexStream(vertexPath);
        std::ifstream fragmentStream(fragmentPath);
        std::string line;
        std::stringstream shaders[2];
        while (getline(vertexStream, line)) {
            shaders[VERTEX] << line << '\n';
        }
        while (getline(fragmentStream, line)) {
            shaders[FRAGMENT] << line << '\n';
        }
        return std::make_pair(shaders[VERTEX].str(), shaders[FRAGMENT].str());
    }

    static unsigned createShader(const std::string& vertexSource, const std::string& fragmentSource) {
        GLuint program = glCreateProgram();
        GLuint vertex = compileShader(GL_VERTEX_SHADER, vertexSource);
        // Collego il codice delle due shader al programma che fa tutto
        glAttachShader(program, vertex);
        GLuint fragment = compileShader(GL_FRAGMENT_SHADER, fragmentSource);
        glAttachShader(program, fragment);

        // Linka e aggiunge a program lo stato (GL_TRUE/FALSE)
        glLinkProgram(program);
        // Utile per debuggare, mette nel program se può essere eseguito, se ha problemi ecc
        //glValidateProgram(program);

        // Ora che ho "compilato e linkato", posso eliminare gli shader intermedi
        // Con detach stacco le shader dal programma
        glDetachShader(program, vertex);
        glDetachShader(program, fragment);
        // Con delete elimino proprio le shader, ma solo se non ancora legate ad un programma
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return program;
    }

    static unsigned compileShader(const unsigned int type, const std::string &source) {
        // Inizio a creare lo shader
        GLuint id = glCreateShader(type);
        const GLchar* src = source.c_str();
        // Carico il codice nello shader, specificando l'id dello shader creato, il numero di shader, il codice effettivo e boh
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        GLint result;
        // getShader mi fa vedere qualcosa dello shader, in questo caso lo stato di compilazione. iv vuol dire che il risultato verrà restituito come intero in un vettore (in realtà un una &reference)
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) { // Se la compilazione non è andata a buon fine
            int length;
            // Mi salvo la lunghezza del messaggio d'errore
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            // Alloco dinamicamente nello stack un blocco di memoria lungo quanto l'errore
            char* errorMessage = static_cast<char*>(alloca(length * sizeof(char)));
            // Mi restituisce l'errore dello shader; gli passo l'id, la massima lunghezza del buffer, mi scrive (di nuovo) la lunghezza dell'errore, e il posto in cui scrivere l'errore
            glGetShaderInfoLog(id, length, &length, errorMessage);
            std::cerr << "Failed to compile a shader (" << type << ")\n" << errorMessage << std::endl;
            // Ha fallito, tanto vale eliminarlo
            glDeleteShader(id);
        }
        return id;
    }

    int getUniformLocation(const std::string &name) const {
        if (uniformLocationCache.find(name) != uniformLocationCache.end()) {
            return uniformLocationCache[name];
        }
        GLint location = glGetUniformLocation(id, name.c_str());
        if (location == -1)
            std::cout << "Warning: uniform \"" << name << "\" doesn't exist" << std::endl;
        else // Cherno ha tolto l'else, ma credo abbia più senso metterlo
            uniformLocationCache[name] = location;
        return location;
    }
};
