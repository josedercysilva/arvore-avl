#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct no{
    int valor;
    struct no *direita,*esquerda;
    int altura;
}noArv;

noArv *novoNo(int x){
    noArv *novo = malloc(sizeof(noArv));
    if (novo != NULL){
        novo->valor = x;
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->altura = 0;
    }
    return novo;
}

int maior(int a, int b){
    if (a > b)
        return a;
    else
        return b;
}

int alturadoNo(noArv *no){
    if (no == NULL){
        return -1;
    }else{
        return no->altura;
    }
}

int fatordeBalanceamento(noArv *no){
    if(no != NULL)
        return (alturadoNo(no->esquerda) - alturadoNo(no->direita));
    else
        return 0;
}

noArv *rotacaoEsquerda(noArv *noRotacao){
    noArv *y, *f;
    y = noRotacao->direita;
    f = y->esquerda;
    
    y -> esquerda = noRotacao;
    noRotacao->direita = f;
    
    noRotacao->altura = maior(alturadoNo(noRotacao->esquerda), alturadoNo(noRotacao->direita)) + 1;
    y->altura = maior(alturadoNo(y->esquerda), alturadoNo(y->direita)) + 1;
    
    return y;
}

noArv *rotacaoDireita(noArv *noRotacao){
    noArv *y, *f;
    y = noRotacao->esquerda;
    f = y->direita;
    
    y -> direita = noRotacao;
    noRotacao->esquerda = f;
    
    noRotacao->altura = maior(alturadoNo(noRotacao->esquerda), alturadoNo(noRotacao->direita)) + 1;
    y->altura = maior(alturadoNo(y->esquerda), alturadoNo(y->direita)) + 1;
    
    return y;
}

noArv *rotacaoDireitaEsquerda(noArv *noRotacao){
    noRotacao->direita = rotacaoDireita(noRotacao->direita);
    return rotacaoEsquerda(noRotacao);
}

noArv *rotacaoEsquerdaDireita(noArv *noRotacao){
    noRotacao->esquerda = rotacaoEsquerda(noRotacao->esquerda);
    return rotacaoEsquerda(noRotacao);
}

noArv *balancear(noArv *raiz){
    int fb = fatordeBalanceamento(raiz);
       
    if (fb < -1 && fatordeBalanceamento(raiz->direita) <= 0)
        raiz = rotacaoEsquerda(raiz);
    else if (fb > 1 && fatordeBalanceamento(raiz->esquerda) >= 0)
        raiz = rotacaoDireita(raiz);
    else if (fb > 1 && fatordeBalanceamento(raiz->esquerda) < 0)
        raiz = rotacaoEsquerdaDireita(raiz);
    else if(fb < -1 && fatordeBalanceamento(raiz->direita) > 0)
        raiz = rotacaoDireitaEsquerda(raiz);
    return raiz;
}

noArv  *inserir_versao_1(noArv *raiz, int num){
    if(raiz == NULL){
        return novoNo(num);
    }else{
        if(num < raiz->valor){
            raiz->esquerda = inserir_versao_1(raiz->esquerda, num);
        }else{
            raiz->direita = inserir_versao_1(raiz->direita, num);
        }
        
        raiz->altura = maior(alturadoNo(raiz->esquerda),alturadoNo(raiz->direita)) + 1;
        raiz = balancear(raiz);
        
        return raiz;
    }
}

noArv *remover(noArv *raiz, int chave){
    if (raiz == NULL){
        return raiz;
    }
    if (chave < raiz->valor){ 
        raiz->esquerda = remover(raiz->esquerda, chave);
    } else if (chave > raiz->valor){ 
        raiz->direita = remover(raiz->direita, chave);
    
    } else {
        if (raiz->esquerda == NULL){
            noArv *aux_deRemocao = raiz->direita;
            free(raiz);
            return aux_deRemocao;
        } else if (raiz->direita == NULL){
            noArv *aux_deRemocao = raiz->esquerda;
            free(raiz);
            return aux_deRemocao;
        } 
        
        noArv *temp = raiz->direita;
        while (temp != NULL && temp->esquerda != NULL){
            temp = temp->esquerda;
        }
        raiz->valor = temp->valor;        
        raiz->direita = remover(raiz->direita, temp->valor);
    }
    
    raiz->altura = maior(alturadoNo(raiz->esquerda),alturadoNo(raiz->direita)) + 1;
    raiz = balancear(raiz);
    return raiz; 
}  
        
void imprimir(noArv *raiz, int nivel){
    int i;
    if (raiz != NULL){
        imprimir(raiz->direita, nivel +1);
        printf("\n\n");
        
        for (i = 0; i < nivel; i++)
        printf("\t");
        
        printf("%d", raiz->valor);
        imprimir(raiz->esquerda, nivel + 1);
    }
}


int main(){
 
    int opcao,valor;
    noArv *raiz = NULL;
    do{
        printf("\n\n\t0 - sair\n\t1 - Inserir\n\t2 - Remover\n\t3 - Imprimir\n\n");
        scanf("%d", &opcao);
        
        switch(opcao){
            case 0:
                printf("\tSaindo!!!");
            break;
            case 1:
                printf("\tDigite o valor a ser inserido: ");
                scanf("%d", &valor);
                raiz = inserir_versao_1(raiz,valor);
            break;
            case 2:
                printf("\tDigite o valor a ser removido: ");
                scanf("%d", &valor);
                raiz = remover(raiz, valor);
            break;
            case 3:
                imprimir(raiz,1);
            break;
                printf("\nOpcao invalida");
        }
    }while(opcao != 0);
    
    
return 0;
}