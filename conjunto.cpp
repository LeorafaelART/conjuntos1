#include "conjunto.h"
namespace ejm {
int Conjunto::getTamanho() const
{
    return tamanho;
}
Conjunto::~Conjunto(){
    if(array) delete[] array;
}
Conjunto::Conjunto(int tamanho):
    tamanho(0),
    indiceOcupacao(0),
    array(0)
{
    if(tamanho <= 0 )
        throw QString("Tamanho do Conjunto não pode ser <= 0");
    try {
        array = new int[tamanho];
        this->tamanho = tamanho;
    } catch (std::bad_alloc &erro) {
        throw QString("Conjunto não foi criado = faltou espaço");
    }
}
QString Conjunto::getConjunto() const{
    QString saida = "{";
    for(int pos = 0; pos < indiceOcupacao; pos++){

        if(pos!=indiceOcupacao-1)
        {
            saida += QString::number(*(array+pos)) + " , ";
        }
        else
        {
            saida += QString::number(*(array+pos)) + " }";
        }

    }
    return saida;
}
bool Conjunto::buscar(int elemento) const{
    for(int pos = 0; pos < indiceOcupacao; pos++){
        if(elemento == *(array+pos)) return true;
    }
    return false;
}
void Conjunto::incluirElemento(int elemento){
    if(indiceOcupacao == tamanho)
       throw QString("Conjunto esta cheio");
    if(buscar(elemento)) throw QString("Elemento já existe");
    if(this-indiceOcupacao == 0) throw QString("Digite um valor");
    *(array+indiceOcupacao) = elemento;
    indiceOcupacao++;
}
Conjunto * Conjunto::uniao(Conjunto const *const P)
{
    int tamanho=this->indiceOcupacao + P->indiceOcupacao, i, j;
    Conjunto *uni = new Conjunto(tamanho);

    for(i=0;i<this->indiceOcupacao;i++)
    {
        for(j=0;j<P->indiceOcupacao && *(this->array+i) != *(P->array+j);j++)
        {
        }
        if(j==P->indiceOcupacao)
        {
            uni->incluirElemento(*(this->array+i));
        }
    }
    for(i=0;i<P->indiceOcupacao;i++)
    {
        for(j=0;j<this->indiceOcupacao && *(P->array+i) != *(this->array+j);j++)
        {
        }
        if(j==this->indiceOcupacao)
        {
            uni->incluirElemento(*(P->array+i));
        }
    }
    for(i=0;i<P->indiceOcupacao;i++)
    {
        for(j=0;j<this->indiceOcupacao && *(P->array+i) != *(this->array+j);j++)
        {
        }
        if(j<this->indiceOcupacao)
        {
            uni->incluirElemento(*(P->array+i));
        }
    }
    return uni;
}

Conjunto * Conjunto::inter(Conjunto const *const P)
{
    int tamanho=this->indiceOcupacao + P->indiceOcupacao, i, j;
    Conjunto *inter = new Conjunto(tamanho);
    for(i=0;i<P->indiceOcupacao;i++)
    {
        for(j=0;j<this->indiceOcupacao && *(P->array+i) != *(this->array+j);j++)
        {
        }
        if(j<this->indiceOcupacao)
        {
            inter->incluirElemento(*(P->array+i));
        }
    }
    return inter;
}
Conjunto * Conjunto::diff(Conjunto const *const P)
{
    int tamanho=this->indiceOcupacao + P->indiceOcupacao, i, j;
    Conjunto *diff = new Conjunto(tamanho);
    bool ver=false;
    for(i=0;i<P->indiceOcupacao;i++)
    {
        for(j=0;j<this->indiceOcupacao && *(P->array+i) != *(this->array+j);j++)
        {
        }
        if(j==this->indiceOcupacao)
        {
            ver = true;
            diff->incluirElemento(*(P->array+i));
        }
    }
    if(!ver) throw QString("{ }");
    return diff;
}
}