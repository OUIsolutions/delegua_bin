"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.default = {
    cabeça: (interpretador, texto) => Promise.resolve(texto[0]),
    cauda: (interpretador, texto) => Promise.resolve(texto.substring(1)),
    contém: (interpretador, texto, caractere) => Promise.resolve(texto.includes(caractere)),
    descarte: (interpretador, texto, posicao) => Promise.resolve(texto.substring(posicao)),
    descarte_enquanto: (interpretador, texto) => Promise.resolve(''),
    divida: (interpretador, texto, separador = ' ') => Promise.resolve(texto.split(separador)),
    injete: (interpretador, texto) => Promise.resolve(''),
    insira: (interpretador, texto, posicao, elemento) => {
        let vetor = texto.split('');
        vetor.splice(posicao - 1, 0, elemento);
        return Promise.resolve(vetor.join(''));
    },
    inteiro: (interpretador, texto) => Promise.resolve(Math.floor(Number(texto))),
    inverta: (interpretador, texto) => Promise.resolve(texto.split('').reduce((texto, caracter) => (texto = caracter + texto), '')),
    junte: (interpretador, texto, separador) => Promise.resolve(texto.split('').join(separador)),
    lista: (interpretador, texto) => Promise.resolve(texto.split('')),
    maiúsculo: (interpretador, texto) => Promise.resolve(texto.toUpperCase()),
    minúsculo: (interpretador, texto) => Promise.resolve(texto.toLowerCase()),
    ordene: (interpretador, texto) => Promise.resolve(texto.split('').sort().join('')),
    qual_tipo: (interpretador, texto) => Promise.resolve('Texto'),
    pegue: (interpretador, texto, caracteres) => Promise.resolve(texto.substring(0, caracteres)),
    pegue_enquanto: (interpretador, texto) => Promise.resolve(''),
    posição: (interpretador, texto, caractere) => Promise.resolve(texto.indexOf(caractere) + 1),
    real: (interpretador, texto) => Promise.resolve(Number(texto)),
    remova: (interpretador, texto, posicao) => {
        let vetor = texto.split('');
        vetor.splice(posicao - 1, 1);
        return Promise.resolve(vetor.join(''));
    },
    selecione: (interpretador, texto) => Promise.resolve(''),
    tamanho: (interpretador, texto) => Promise.resolve(texto.length),
    último: (interpretador, texto) => Promise.resolve(texto.length > 0 ? texto[texto.length - 1] : ''),
};
//# sourceMappingURL=primitivas-texto.js.map