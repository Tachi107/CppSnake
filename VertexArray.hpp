#pragma once

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

/*
 * Il vertex array collega l'impostazione del buffer (bind e data) in un unico comando.
 * Ciò avviene quando, dopo aver chiamato bindBuffer, chiamo VertexAttribPointer col relativo indice
 * Se chiamo VertexAttribPointer con indice 1 mentre ho bindato un altro buffer e c'è lo stesso vertexArray bindato
 * quel buffer verrà aggiunto al secondo indice del vertexArray.
 * Un vertex array serve per dare una disposizione ai byte di un vertex buffer
 */

class VertexArray {
private:
    GLuint id;

public:
    VertexArray() {
        glGenVertexArrays(1, &id);
    }

    ~VertexArray() {
        glDeleteVertexArrays(1, &id);
    }

    void bind() const {
        glBindVertexArray(id);
    }

    static void unbind() {
        glBindVertexArray(0);
    }

    void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout) {
        bind();
        vertexBuffer.bind();
        const std::vector<VertexBufferElement>& elements = layout.getElements();
        // Offset in byte per passare da un elemento all'altro
        uintptr_t offset = 0;
        /*
         *  È un ciclo perché creo un layout per attibuto (dimensione, texture...) e li unisco tutti in un VertexArray,
         *  coi rispettivi buffer. Ogni buffer senza layout sarebbe un mucchio di dati senza senso.
         *  Col vertex array posso unire una serie di buffer e layout
         */
        for (size_t i = 0; i < elements.size(); i++) {
            const auto& element = elements[i];
            // Ora che ho selezionato e riempito il buffer posso chiamare la funzione che definisce gli attributi dei vertici del triangolo (posizione, colore, texture ecc)
            // L'indice dell'attributo a cui mi sto riferendo (coordinate) (se ho più di un attributo, saprò poi quale sarà l'indice di ognuno di essi), numero di float per coordinata, tipo di dati, se devo normalizzare un numero (se ho un colore, 0 - 255, lui me lo trasforma in un float leggibile dalla gpu), numero di byte di distanza tra una coordinata e l'altra, posizione in byte dell'attributo che sto settando (se ho 2 float per le coordinate, 8 per il colore, e 12 per il soos, le coordinate saranno a 0, il colore a (float * 2 = 8), e il soos a (8 + sizeof(colore) = 16))
            glVertexAttribPointer(i, element.count, static_cast<GLenum>(element.type), GL_FALSE, layout.getStride(), (const void*)offset);
            offset += element.count * VertexBufferElement::sizeOfGlType(element.type); // 3 * sizeof(float)
            glEnableVertexAttribArray(i);
        }
    }
};
