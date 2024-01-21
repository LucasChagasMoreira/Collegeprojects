#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>
#include <ostream>
#include <thread>
#include <vector>
#include <chrono>
#include <time.h>

using namespace std;

class Buffer{
private:
    int capacidademax;
    std::vector<int> buffer;

    pthread_mutex_t mutex;
    pthread_cond_t Produtor;
    pthread_cond_t Consumidor;

    static int itensproduzidos;
    static int itensconsumidos;

public:
    Buffer(int capacidade = 100){
        capacidademax = capacidade;

        pthread_mutex_init(&mutex, NULL);
        pthread_cond_init(&Produtor, NULL);
        pthread_cond_init(&Consumidor, NULL);
    };

    void inseriritem(int item){
        itensproduzidos++;
        buffer.push_back(item);
    };

    int removeitem(){
        int item = buffer.front();
        buffer.pop_back();
        itensconsumidos++;
        return item;
    };
    
    int buffersize(){
        return buffer.size();
    };

    void down(){
        pthread_mutex_trylock(&mutex);
    };

    void up(){
        pthread_mutex_unlock(&mutex);
    };

    void consumidordown(){
        while(buffersize() == 0){
            pthread_cond_wait(&Consumidor, &mutex);
        }
    };

    void Produtordown(){
        while(buffersize() == capacidademax){
            pthread_cond_wait(&Produtor, &mutex);
        }
    };

    void produtoup(){
        pthread_cond_signal(&Produtor);
    };

    void consumidorup(){
        pthread_cond_signal(&Consumidor);
    };

    void producao(int item){
        Produtordown();
        down();
        inseriritem(item);
        up();
        consumidorup();
    };

    void consumir(int & item){
        consumidordown();
        down();
        item = removeitem();
        up();
        produtoup();
    };
    int getitenproduzidos(){
        return itensproduzidos;
    };

    int getitensconsumidos(){
        return itensconsumidos;
    }
};
int Buffer :: itensproduzidos = 0;
int Buffer :: itensconsumidos = 0;

class Produtor{
    private:
        Buffer * buffer;
        int quantidadeitensproduzir;
        int itenspersec;
    public:
        Produtor(Buffer * buffer,int quantidadeitensproduzir, int itenspersec){
            this->buffer = buffer;
            this->quantidadeitensproduzir = quantidadeitensproduzir;
            this->itenspersec = itenspersec;
        }
        void run(){
            int item;
            
            int temposleep = 1000 / itenspersec;
            for(int i = 0; i< quantidadeitensproduzir; i++){
                item = rand();
                buffer->producao(item);
                cout << "item adicionado: " << item << endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(temposleep));
            }
        }
};

class Consumidor{
    private:
        Buffer * buffer;
        int quantidadeitensconsumir;
        int consumopersec;

    public:
        Consumidor(Buffer * buffer,int quantidadeitensconsumir, int consumopersec){
            this->buffer = buffer;
            this->quantidadeitensconsumir = quantidadeitensconsumir;
            this->consumopersec = consumopersec;
        }
        void run(){
            int item;
            
            int temposleep = 1000 / consumopersec;
            for(int i = 0; i< quantidadeitensconsumir; i++){
                
                buffer->consumir(item);
                
                cout << i+1 <<" Item removido: "<< item << endl;
                this_thread::sleep_for(std::chrono::milliseconds(temposleep));
            }
        }
};

void *execconsumidor(void * consumidor){
   
    Consumidor *consumidor1 = static_cast<Consumidor*>(consumidor);
    consumidor1->run();
    pthread_exit(NULL);
}

void *execprodutor(void * produtor){
    
    Produtor *produtor1 = static_cast<Produtor*>(produtor);
    produtor1->run();
    pthread_exit(NULL);
}
int main(){
    
    cout << "digite o tamanho do buffer" << endl;
    int resposta;
    cin >> resposta;

    cout << "digite a quantidade de itens a serem produzidos" << endl;
    int qtditensproduzir;
    int itenpersecproduzir;
    cin >> qtditensproduzir;
    cout << "digite os itens produzidos por segundo " << endl;
    cin >> itenpersecproduzir;
    
    cout << "digite a quantidade de itens a serem consumidos" << endl;
    int qtditensconsumir;
    int itenpersecconsumir;
    cin >> qtditensconsumir;
    cout << "digite os itens consumidos por segundo " << endl;
    cin >> itenpersecconsumir;

    Buffer buffer(resposta);
    Consumidor consumidor(&buffer, qtditensconsumir, itenpersecconsumir);
    Produtor produtor(&buffer, qtditensproduzir,itenpersecproduzir);

    pthread_t threads[2];

    pthread_create(&threads[1], NULL, execprodutor,static_cast<void *>(&produtor));
    pthread_create(&threads[0], NULL, execconsumidor,static_cast<void *>(&consumidor));

    for(int i = 0; i<2; i++){
        pthread_join(threads[i],NULL);
    }

    cout << "quantidade de itens produzidos: " << buffer.getitenproduzidos() << endl;
    cout << "quantidade de itens consumidos: " << buffer.getitensconsumidos() << endl;
    
    return 0;

}