"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.default = {
    arredonde: (interpretador, numero) => Promise.resolve(Math.ceil(numero)),
    caractere: (interpretador, numero) => Promise.resolve(String.fromCharCode(numero)),
    inteiro: (interpretador, numero) => Promise.resolve(Math.floor(numero)),
    qual_tipo: (interpretador, numero) => Promise.resolve(Math.floor(numero) === numero ? 'Inteiro' : 'Real'),
    piso: (interpretador, numero) => Promise.resolve(Math.floor(numero)),
    real: (interpretador, numero) => Promise.resolve(numero),
    teto: (interpretador, numero) => Promise.resolve(Math.ceil(numero)),
    texto: (interpretador, numero) => Promise.resolve(String(numero)),
};
//# sourceMappingURL=primitivas-numero.js.map