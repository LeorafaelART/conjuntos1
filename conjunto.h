#ifndef CONJUNTO_H
#define CONJUNTO_H
#include<QString>
namespace ejm {
class Conjunto
{
    //Atributos
private:
    int tamanho;
    int indiceOcupacao;
    int *array;
public:
    Conjunto(int tamanho);
    ~Conjunto();
    int getTamanho() const;
    QString getConjunto() const;

    //para verificar e incluir elemntos do conjunto
    bool buscar(int elemento) const;
    void incluirElemento(int elemento);

    //metodos para os conjuntos
    Conjunto *uniao(Conjunto const *const P);
    Conjunto *inter(Conjunto const *const P);
    Conjunto *diferenca(Conjunto const *const P);

    bool subconjunto (Conjunto const * const P);
    bool disjunto(Conjunto const *const P);
    bool eVazio()const;
    float media()const;
    bool eIndentico(const Conjunto * const P);
    int amplitude()const;
   ;


};

}
#endif // CONJUNTO_H
