#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct no{
	int chave;
	int qtdProx;
	struct no *prox;
};
typedef struct no NO;

void adicionar(NO* hash[], int posicaoAdd, int chave, int tamHash){
    if(hash[posicaoAdd]->chave == 0){
        hash[posicaoAdd]->chave = chave;
    }else{
        if(hash[posicaoAdd]->prox != NULL){
            int contador = 0;
            int posicao = posicaoAdd;
            while(contador < hash[posicaoAdd]->qtdProx){
                for(int i=tamHash-1; i>=0; i--){
                    if(hash[i]->chave == hash[posicao]->prox->chave){
                        //printf("ENTREI AQ \n");
                        posicao = i;
                        contador++;
                        break;
                    }
                }
            }
            //printf("Valor certo da posicao do prox: %i \n", posicao);
            for(int i=tamHash-1; i>=0; i--){
                if(hash[i]->chave == 0){
                    hash[i]->chave = chave;
                    hash[posicao]->prox = hash[i];
                    hash[posicaoAdd]->qtdProx = hash[posicaoAdd]->qtdProx + 1;
                    break;
                }
            }
        }else{
            for(int i=tamHash-1; i>=0; i--){
                if(hash[i]->chave == 0){
                    hash[posicaoAdd]->prox = hash[i];
                    hash[i]->chave = chave;
                    printf("\n%i \n", hash[posicaoAdd]->prox->chave);
                    hash[posicaoAdd]->qtdProx = hash[posicaoAdd]->qtdProx + 1;
                    break;
                }
            }
        }
    }
}

int buscar(NO* hash[], int posicaoAdd, int chave){
    NO* aux = hash[posicaoAdd];
    while(aux != NULL){
        if(aux->chave == chave){
            printf("A chave ja existe...\n");
            return 1;
        }else{
            aux = aux->prox;
        }
    }
    return 2;
}

void remover(NO* hash[], int posicaoAdd, int chave, int tamHash){
    if(hash[posicaoAdd]->chave == chave){
        if(hash[posicaoAdd]->prox == NULL){
            hash[posicaoAdd]->chave = 0;
        }else{
            if(hash[posicaoAdd]->prox->prox == NULL){
                hash[posicaoAdd]->chave = hash[posicaoAdd]->prox->chave;
                hash[posicaoAdd]->prox->chave = 0;
                hash[posicaoAdd]->prox = NULL;
                hash[posicaoAdd]->qtdProx = hash[posicaoAdd]->qtdProx - 1;
            }else{
                hash[posicaoAdd]->chave = hash[posicaoAdd]->prox->chave;
                hash[posicaoAdd]->prox->chave = 0;
                hash[posicaoAdd]->prox = hash[posicaoAdd]->prox->prox;
                hash[posicaoAdd]->qtdProx = hash[posicaoAdd]->qtdProx - 1;
                //printf("%i \n", hash[posicaoAdd]->prox->chave);
                //printf("%i \n", hash[posicaoAdd]->qtdProx);
            }
        }
    }else{
        if(hash[posicaoAdd]->prox->chave == chave){
            if(hash[posicaoAdd]->prox->prox == NULL){
                //printf("Entrei nesse iF \n");
                hash[posicaoAdd]->prox->chave = 0;
                hash[posicaoAdd]->prox = NULL;
                hash[posicaoAdd]->qtdProx = hash[posicaoAdd]->qtdProx - 1;
                printf("%i \n", hash[posicaoAdd]->qtdProx);
            }else{
                //printf("Entrei nesse outro iF \n");
                hash[posicaoAdd]->prox->chave = 0;
                hash[posicaoAdd]->prox = hash[posicaoAdd]->prox->prox;
                hash[posicaoAdd]->qtdProx = hash[posicaoAdd]->qtdProx - 1;
                //printf("%i \n", hash[posicaoAdd]->prox->chave);
                //printf("%i \n", hash[posicaoAdd]->qtdProx);
            }
        }else{
            //printf("ENtrei no else do remover.... \n");
            int contador = 0;
            int posicao = posicaoAdd;
            while(contador < hash[posicaoAdd]->qtdProx){
                for(int i=tamHash-1; i>=0; i--){
                    if(hash[i]->chave == hash[posicao]->prox->chave){
                        //printf("ENTREI AQ NO IF DO REMOVER SEM TAR NA POSICAO CERTA \n");
                        posicao = i;
                        contador++;
                        break;
                    }
                }
                if(hash[posicao]->prox->chave == chave){
                    //printf("ENtrei no if que tem que sair do while... \n");
                    break;
                }
            }
            //printf("EU sai do WHILE.... \n");
            if(hash[posicao]->prox->prox == NULL){
                //printf("Entrei nesse iF \n");
                hash[posicao]->prox->chave = 0;
                hash[posicao]->prox = NULL;
                hash[posicaoAdd]->qtdProx = hash[posicaoAdd]->qtdProx - 1;
                //printf("%i \n", hash[posicaoAdd]->qtdProx);
            }else{
                //printf("Entrei nesse outro iF \n");
                hash[posicao]->prox->chave = 0;
                hash[posicao]->prox = hash[posicao]->prox->prox;
                hash[posicaoAdd]->qtdProx = hash[posicaoAdd]->qtdProx - 1;
                //printf("%i \n", hash[posicao]->prox->chave);
                //printf("%i \n", hash[posicaoAdd]->qtdProx);
            }
        }
    }
}

int metodoDaDivisao(int tamHash, int chave){
    return chave % tamHash;
}

//METODO DA MULTIPLICAÇÃO
/*int metodoMultiplicacao(int chave, int tamTabela){
    //int retorno = (int) (tamTabela * (( (int) chave*0.61803) % 1));
    int aux = (int) chave * 0.61803981;
    float aux2 = chave * 0.61803981;
    float result = aux2 - aux;
    int retorno = (int) tamTabela * result;
    return retorno;
}*/

int verificaTamHash(float tamHash){
    float x;
    for(int i=1; i<=20; i++){
        x = pow(10, i);
        if(x == tamHash){
            return 1;
        }
    }
    return -1;
}

int mult(int chave, int tamHash){
    int auxiliar = tamHash;
    int contador = 0;
    while(auxiliar > 0){
        auxiliar = auxiliar/10;
        contador++;
    }
    float verificador = tamHash;
    int isPotencia = verificaTamHash(verificador);
    if(isPotencia == 1){
        contador--;
    }

    //printf("qtd de digitos pra pegar do vetor final: %i \n", contador);

    int auxChave = chave * chave;
    int contador2 = 0;
    while(auxChave > 0){
        auxChave = auxChave/10;
        contador2++;
    }
    //printf("tamanho do vetor: %i \n", contador2);
    int vetorResult[contador2];
    int auxiliar3 = chave*chave;
    int x = 0;
    for(int i=contador2-1; i>=0; i--){
        x = auxiliar3 % 10;
        vetorResult[i] = x;
        auxiliar3 = auxiliar3/10;
    }
    for(int i=0; i<contador2; i++){
        //printf("Posicao %i do vetor: %i \n", i, vetorResult[i]);
    }

    int retorno = chave*chave;
    if(retorno < tamHash){
        return retorno;
    }else{
        int vetor[contador];
        int x = contador;
        int aux = 0;
        int i = contador2/2;
        //printf("Valor original do i: %i \n", i);
        if(contador2 % 2 == 0){
            i--;
        }
        //printf("Valor do i: %i \n", i);
        while(x > 0){
            vetor[aux] = vetorResult[i];
            i++;
            x--;
            aux++;
        }
        printf("\n \n");
        for(int i=0; i<contador; i++){
            printf("%i \n", vetor[i]);
        }
        printf("\n \n");
        if(contador == 1){
            //printf("hahaha: %i \n", vetor[0]);
            return vetor[0];
        }else{
            int result = 0;
            int m = 1;
            for(int i=contador-1; i>=0; i--){
                result = result + (vetor[i] * m);
                //printf("Valor do mult q vai almentando: %i \n", result);
                m = m*10;

            }
            //printf("Add na posicao: %i \n", result);
            return result;
        }
    }
}



//METODOS DA DOBRA (AND< XOR E OR)
void convertebinario(int vetor[], int chave){
    //printf("Chave %i em binario: ", chave);
    for (int aux = 9; aux >= 0; aux--){
        if (chave % 2 == 0){
            vetor[aux] = 0;
        }else{
            vetor[aux] = 1;
        }
        chave = chave / 2;
    }
    for(int i=0; i<=9; i++){
        //printf("%i, ", vetor[i]);
    }
}

int converteInteiro(int vetor[]){
    int soma = 0;
    int potencia = 0;
    for(int i=4; i>=0; i--){
        if(vetor[i] == 1){
            soma += pow(2, potencia);
        }
        potencia++;
    }
    return soma;
}

void and(int vetorEntrada[], int vetorSaida[]){
    for(int i=0; i<=4; i++){
        if((vetorEntrada[i] == 1 && vetorEntrada[i+5] == 1)){
            vetorSaida[i] = 1;
        }else{
            vetorSaida[i] = 0;
        }
    }
}

void or(int vetorEntrada[], int vetorSaida[]){
    for(int i=0; i<=4; i++){
        if((vetorEntrada[i] == 0 && vetorEntrada[i+5] == 0)){
            vetorSaida[i] = 0;
        }else{
            vetorSaida[i] = 1;
        }
    }
}

void xor(int vetorEntrada[], int vetorSaida[]){
    for(int i=0; i<=4; i++){
        if((vetorEntrada[i] == 0 && vetorEntrada[i+5] == 1) || (vetorEntrada[i] == 1 && vetorEntrada[i+5] == 0)){
            vetorSaida[i] = 1;
        }else{
            vetorSaida[i] = 0;
        }
    }
}

int metodoDobra(int chave){
    int vetor[10];
    convertebinario(vetor, chave);
    int vetResult[5];
    xor(vetor, vetResult);
    int retorno;
    retorno = converteInteiro(vetResult);
    printf("Adicionar na posicao: %i da hash", retorno);
    return retorno;
}


//METODOS DA ANALISE DOS DIGITOS
double calcSoma(int qtdDigito, int tamVetor){
    double aux = qtdDigito;
    double aux2 = tamVetor;
    double retorno;
    retorno = (double) aux - (aux2/10);
    if(retorno < 0){
        retorno = retorno * -1;
    }
    return retorno;
}

double contaDigitos(int vetor[], int tamVetor){
    int dig0 = 0;
    int dig1 = 0;
    int dig2 = 0;
    int dig3 = 0;
    int dig4 = 0;
    int dig5 = 0;
    int dig6 = 0;
    int dig7 = 0;
    int dig8 = 0;
    int dig9 = 0;

    for(int i=0; i<tamVetor; i++){
        if(vetor[i] == 0){
            dig0++;
        }else if(vetor[i] == 1){
            dig1++;
        }else if(vetor[i] == 2){
            dig2++;
        }else if(vetor[i] == 3){
            dig3++;
        }else if(vetor[i] == 4){
            dig4++;
        }else if(vetor[i] == 5){
            dig5++;
        }else if(vetor[i] == 6){
            dig6++;
        }else if(vetor[i] == 7){
            dig7++;
        }else if(vetor[i] == 8){
            dig8++;
        }else if(vetor[i] == 9){
            dig9++;
        }
    }

    double somadig0 = calcSoma(dig0, tamVetor);
    double somadig1 = calcSoma(dig1, tamVetor);
    double somadig2 = calcSoma(dig2, tamVetor);
    double somadig3 = calcSoma(dig3, tamVetor);
    double somadig4 = calcSoma(dig4, tamVetor);
    double somadig5 = calcSoma(dig5, tamVetor);
    double somadig6 = calcSoma(dig6, tamVetor);
    double somadig7 = calcSoma(dig7, tamVetor);
    double somadig8 = calcSoma(dig8, tamVetor);
    double somadig9 = calcSoma(dig9, tamVetor);

    double soma = somadig0 + somadig1 + somadig2 + somadig3 + somadig4 + somadig5 + somadig6 + somadig7 + somadig8 + somadig9;

    return soma;
}

double analiseDigitos(int casaDecimal, int vetor[], int tamVetor){
    int aux = casaDecimal;
    int vetorAux[tamVetor];
    double vetorResult[casaDecimal];
    int contador = 0;
    double soma;
    while(aux != 0){
        for(int i=0; i<tamVetor; i++){
            vetorAux[i] = (vetor[i] % 10);
        }
        for(int i=0; i<tamVetor; i++){
            vetor[i] = vetor[i] / 10;
        }
        soma = contaDigitos(vetorAux, tamVetor);
        vetorResult[contador] = soma;
        contador++;
        aux--;
    }
    double menorResult = vetorResult[0];
    //printf("%f \n", vetorResult[0]);
    for(int i=1; i<casaDecimal; i++){
      //  printf("%f \n", vetorResult[i]);
        if(menorResult > vetorResult[i]){
            menorResult = vetorResult[i];
        }
    }
    int gambiarra = 0;
    for(int i=casaDecimal-1; i>=0; i--){
        if(vetorResult[i] == menorResult){
            break;
        }
        gambiarra++;
    }
    return gambiarra+1;
}

int retornaPosicaoAdd(int numero, int casaDecimal, int digito){
    int aux = numero;
    int aux1 = casaDecimal;
    int aux2 = digito;
    int retorno = 0;

    while(aux > 0){
        if(aux1 == aux2){
            retorno = aux % 10;
            return retorno;
        }
        aux = aux / 10;
        aux1--;
    }
}

int verificaCasaDecimal(int chave, int casaDecimal){
    if(casaDecimal == 1){
        if(chave >=1 && chave <10){
            return 1;
        }else{
            return 2;
        }
    }else if(casaDecimal == 2){
        if(chave >=10 && chave <100){
            return 1;
        }else{
            return 2;
        }
    }else if(casaDecimal == 3){
        if(chave >=100 && chave <1000){
            return 1;
        }else{
            return 2;
        }
    }else if(casaDecimal == 4){
        if(chave >=1000 && chave <10000){
            return 1;
        }else{
            return 2;
        }
    }else if(casaDecimal == 5){
        if(chave >=10000 && chave <100000){
            return 1;
        }else{
            return 2;
        }
    }else{
        if(chave >=100000 && chave <1000000){
            return 1;
        }else{
            return 2;
        }
    }
}

void imprimeHash(NO* hash[], int tamHash){
    for(int i=0; i<tamHash; i++){
        printf("\nPosicao %i: %i", i, hash[i]->chave);
    }
}

void mainMultiplicacao(){
    int tamHash;
    printf("Digite o tamanho da hash: ");
    scanf("%i", &tamHash);

    NO* hash[tamHash];
    for(int i=0; i<tamHash; i++){
        hash[i] = malloc(sizeof(NO));
        hash[i]->prox = NULL;
        hash[i]->chave = 0;
        hash[i]->qtdProx = 0;
    }


    int valor;
    for(int i=0; i<4; i++){
        printf("\n Digite o valor que quer add: ", i);
        scanf("%i", &valor);
        int x = mult(valor, tamHash);
        int aux = buscar(hash, x, valor);
        if(aux == 1){
            i--;
        }else{
            adicionar(hash, x, valor, tamHash);
        }
    }

    imprimeHash(hash, tamHash);

    for(int i=0; i<3; i++){
        int aux = 0;
        printf("\n Digite o valor que esta procurando: ");
        scanf("%i", &aux);
        int x = mult(aux, tamHash);
        int aux1 = buscar(hash, x, aux);
        if(aux1 != 1){
            printf("Chave inexistente... \n");
        }
    }

    for(int i=0; i<1; i++){
        int aux = 0;
        printf("\n Digite o valor que quer remover: ");
        scanf("%i", &aux);
        int x = mult(aux, tamHash);
        int aux1 = buscar(hash, x, aux);
        if(aux1 == 1){
            remover(hash, x, aux, tamHash);
        }else{
            printf("Chave inexistente... \n");
        }
    }

    imprimeHash(hash, tamHash);
}

void mainDivisao(){
    int tamHash;
    printf("Digite o tamanho da hash: ");
    scanf("%i", &tamHash);

    NO* hash[tamHash];
    for(int i=0; i<tamHash; i++){
        hash[i] = malloc(sizeof(NO));
        hash[i]->prox = NULL;
        hash[i]->chave = 0;
        hash[i]->qtdProx = 0;
    }


    int valor;
    for(int i=0; i<4; i++){
        printf("\n Digite o valor que quer add: ", i);
        scanf("%i", &valor);
        int x = metodoDaDivisao(tamHash, valor);
        int aux = buscar(hash, x, valor);
        if(aux == 1){
            i--;
        }else{
            adicionar(hash, x, valor, tamHash);
        }
    }

    imprimeHash(hash, tamHash);

    for(int i=0; i<3; i++){
        int aux = 0;
        printf("\n Digite o valor que esta procurando: ");
        scanf("%i", &aux);
        int x = metodoDaDivisao(tamHash, aux);
        int aux1 = buscar(hash, x, aux);
        if(aux1 != 1){
            printf("Chave inexistente... \n");
        }
    }

    for(int i=0; i<1; i++){
        int aux = 0;
        printf("\n Digite o valor que quer remover: ");
        scanf("%i", &aux);
        int x = metodoDaDivisao(tamHash, aux);
        int aux1 = buscar(hash, x, aux);
        if(aux1 == 1){
            remover(hash, x, aux, tamHash);
        }else{
            printf("Chave inexistente... \n");
        }
    }

    imprimeHash(hash, tamHash);
        int messi = 0;
        printf("\n Digite o valor que quer add: ");
        scanf("%i", &messi);
        int x3 = metodoDaDivisao(tamHash, messi);
        adicionar(hash, x3, messi, tamHash);
    imprimeHash(hash, tamHash);


    int pele = 0;
    printf("\n Digite o valor que esta procurando: ");
    scanf("%i", &pele);
        int x4 = metodoDaDivisao(tamHash, pele);
        int aux7 = buscar(hash, x4, pele);
        if(aux7 != 1){
            printf("Chave inexistente... \n");
        }


}

void mainDobra(){
    int tamHash;
    printf("Digite o tamanho da hash: ");
    scanf("%i", &tamHash);

    NO* hash[tamHash];
    for(int i=0; i<tamHash; i++){
        hash[i] = malloc(sizeof(NO));
        hash[i]->prox = NULL;
        hash[i]->chave = 0;
        hash[i]->qtdProx = 0;
    }


    int valor;
    for(int i=0; i<4; i++){
        printf("\n Digite o valor que quer add: ", i);
        scanf("%i", &valor);
        int x = metodoDobra(valor);
        int aux = 0;
        if(x < tamHash){
            aux = buscar(hash, x, valor);
        }

        if(aux == 1){
            i--;
        }else{
            if(x >= tamHash){
                printf("Nao foi possivel add o valor %i, pois a posicao gerada na tabela nao existe... \n", x);
            }else{
                adicionar(hash, x, valor, tamHash);
            }
        }
    }

    imprimeHash(hash, tamHash);

    for(int i=0; i<3; i++){
        int aux = 0;
        printf("\n Digite o valor que esta procurando: ");
        scanf("%i", &aux);
        int x = metodoDobra(aux);
        int aux1 = buscar(hash, x, aux);
        if(aux1 != 1){
            printf("Chave inexistente... \n");
        }
    }

    for(int i=0; i<1; i++){
        int aux = 0;
        printf("\n Digite o valor que quer remover: ");
        scanf("%i", &aux);
        int x = metodoDobra(aux);
        int aux1 = buscar(hash, x, aux);
        if(aux1 == 1){
            remover(hash, x, aux, tamHash);
        }else{
            printf("CHave inexistente... \n");
        }
    }
    imprimeHash(hash, tamHash);
}

void mainAnaliseDosDigitos(){
    int tamHash;
    printf("Digite o tamanho da hash: ");
    scanf("%i", &tamHash);

    NO* hash[tamHash];
    for(int i=0; i<tamHash; i++){
        hash[i] = malloc(sizeof(NO));
        hash[i]->prox = NULL;
        hash[i]->chave = 0;
        hash[i]->qtdProx = 0;
    }

    int casaDecimal = 0;
    printf("\nDigite a casa decimal dos valores a serem adicionados: ");
    scanf("%i", &casaDecimal);

    int vetor[tamHash];

    for(int i=0; i<tamHash; i++){
        int aux = 0;
        printf("\nDigite o valor que deseja adicionar na posicao %i do vetor: ", i);
        scanf("%i", &aux);
        int aux2 = verificaCasaDecimal(aux, casaDecimal);
        if(aux2 == 1){
            vetor[i] = aux;
        }else{
            printf("\n O valor digitado nao atende a qtd de casas decimais... Digite novamente \n");
            i--;
        }
    }

    int vetAux[tamHash];
    for(int x=0; x<tamHash; x++){
        vetAux[x] = vetor[x];
    }

    int result = analiseDigitos(casaDecimal, vetAux, tamHash);
    printf("Add na hash no digito: %i \n", result);


    for(int i=0; i<tamHash; i++){
        int auxiliar = 0;
        printf("%i \n", vetor[i]);
        auxiliar = retornaPosicaoAdd(vetor[i], casaDecimal, result);
        adicionar(hash, auxiliar, vetor[i], tamHash);
    }

    imprimeHash(hash, tamHash);

    for(int i=0; i<3; i++){
        int aux = 0;
        printf("\n Digite o valor que esta procurando: ");
        scanf("%i", &aux);
        int x = retornaPosicaoAdd(aux, casaDecimal, result);
        int aux1 = buscar(hash, x, aux);
        if(aux1 != 1){
            printf("Chave inexistente... \n");
        }
    }

    for(int i=0; i<1; i++){
        int aux = 0;
        printf("\n Digite o valor que quer remover: ");
        scanf("%i", &aux);
        int x = retornaPosicaoAdd(aux, casaDecimal, result);
        int aux1 = buscar(hash, x, aux);
        if(aux1 == 1){
            remover(hash, x, aux, tamHash);
        }
    }

    imprimeHash(hash, tamHash);

}

void main(){
    mainDivisao();
    //mainMultiplicacao();
    //mainDobra();
    //mainAnaliseDosDigitos();
}
