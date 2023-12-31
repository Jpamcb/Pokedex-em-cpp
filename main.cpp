#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "pokemon.h"

using namespace std;

void Numero(int i, Time* time, ofstream& Info){
    //Exibe o número do pokémon na pokédex e coloca-o dentro de um arquivo
    if(time[i].dex < 10){
        cout << " <00" << time[i].dex << ">" << endl;
        Info << " <00" << time[i].dex << ">" << endl;
    }else if(time[i].dex < 100){
        cout << " <0" << time[i].dex << ">" << endl;
        Info << " <0" << time[i].dex << ">" << endl;
    }else{
        cout << " <" << time[i].dex << ">" << endl;
        Info << " <" << time[i].dex << ">" << endl;
    }
}

void Tipo(Time* time, int i, ofstream& Info){
    //Exibe as possíveis duas tipagens do pokémon
    string tipagem[18] = {"Normal", "Fogo", "Agua", "Planta", "Voador", "Lutador", "Veneno", "Eletrico", "Terra", "Pedra", "Psiquico", "Gelo", "Inseto", "Fantasma", "Metal", "Dragao", "Sombrio", "Fada"};
    
    cout << "Tipo: " << tipagem[time[i].tipo];
    Info << "Tipo: " << tipagem[time[i].tipo];
    if(time[i].stipo != -1){
        cout << " e " << tipagem[time[i].stipo];
        Info << " e " << tipagem[time[i].stipo];
    }
}

void Pokemon::Preencher(ifstream& arquivo, Pokemon* Dex){
    //Retira as informações do arquivo e armazena em um vetor
    Pokemon pokemon;
    string linha;
    int cont = 0;

    while(getline(arquivo, linha)){
        string dex2, nome2, tipo2, stipo2, altura2, peso2, evolvl2, final2;
        istringstream lin(linha);
        if(lin >> dex2 >> nome2 >> tipo2 >> stipo2 >> altura2 >> peso2 >> evolvl2 >> final2){
            pokemon.dex = stoi(dex2);
            pokemon.nome = nome2;
            pokemon.tipo = stoi(tipo2);
            pokemon.stipo = stoi(stipo2);
            pokemon.altura = stof(altura2);
            pokemon.peso = stof(peso2);
            pokemon.evolvl = stoi(evolvl2);
            pokemon.final = stoi(final2);
        }
        Dex[cont] = pokemon;
        cont++;
    }
};

void Pokemon::Exibir(Pokemon* Dex){
    //Apresenta todos os nomes dos pokémons e seus respectivos números ao usuário
    for(int i = 0; i < 151; i++){
        cout << Dex[i].dex << " " << Dex[i].nome << endl;
    }
}

void Time::InfoAdicionais(Time* time){
    //Armazena as informações de stats e possíveis habilidades aos 6 pokemons escolhidos
    int encontrar = 1;
    ifstream info;
    string linha;
    Time t;

    for(int i = 0; i < 6; i++){
        info.open("stats.txt");
        encontrar = 1;
        
        while(getline(info, linha)){
            string hp, atk, def, spatk, spdef, spe, total;
            istringstream lin(linha);
            if(lin >> hp >> atk >> def >> spatk >> spdef >> spe >> total){
                if(time[i].dex == encontrar){
                    time[i].stats[0] = stoi(hp);
                    time[i].stats[1] = stoi(atk);
                    time[i].stats[2] = stoi(def);
                    time[i].stats[3] = stoi(spatk);
                    time[i].stats[4] = stoi(spdef);
                    time[i].stats[5] = stoi(spe);
                    time[i].stats[6] = stoi(total);
                }
            }
            encontrar++;
        }
        info.close();
    }

    for(int i = 0; i < 6; i++){
        info.open("habilidades.txt");
        encontrar = 1;
        string hab;

        while(getline(info, linha)){
            if(time[i].dex == encontrar){
                time[i].hab = linha;
            }
            encontrar++;
        }

        info.close();
    }
}

void Time::Preencher(Time* time, Pokemon*Dex){
    //Solicita 6 pokémons ao usuário e os armazena em um vetor
    string nome;
    int cont = 0;

    cout << "Escolha 6 pokemons para o seu time!\n";
    while(cont < 6){
        int encontrar = 0;
        cin >> nome;
        
        for(int i = 0; i < 151; i++){
            if(Dex[i].nome == nome){
                time[cont].dex = Dex[i].dex;
                time[cont].nome = Dex[i].nome;
                time[cont].tipo = Dex[i].tipo;
                time[cont].stipo = Dex[i].stipo;
                time[cont].altura = Dex[i].altura;
                time[cont].peso = Dex[i].peso;
                time[cont].evolvl = Dex[i].evolvl;
                time[cont].final = Dex[i].final;
                encontrar++;
                cont++;
            }
        }
        if(encontrar == 0){
                cout << "Parece que você escreveu o nome errado... Lembre-se de considerar letras maiúsculas e minúsculas" << endl;
        }
    }
    InfoAdicionais(time);
}

void Time::Exibir(Time* time, Pokemon* Dex, ofstream& Info){
    //Exibe todas as informações dos 6 pokémons escolhidos e armazena as mesmas em um arquivo
    for(int i = 0; i < 6; i++){
        cout << endl << endl;
        cout << "Pokemon: " << time[i].nome;
        Info << "Pokemon: " << time[i].nome;
        Numero(i, time, Info);
        Tipo(time, i, Info);
        cout << endl << "Altura: " << fixed << setprecision(2) << time[i].altura << "m  |  Peso: " << time[i].peso << "kg" << endl;
        Info << endl << "Altura: " << fixed << setprecision(2) << time[i].altura << "m  |  Peso: " << time[i].peso << "kg" << endl;
        cout << "Stats: HP(" << time[i].stats[0] << ") ATK(" << time[i].stats[1] << ") DEF(" << time[i].stats[2] << ") SP.ATK(" << time[i].stats[3] << ") SP.DEF(" << time[i].stats[4] << ") SPE(" << time[i].stats[5] << ") Total(" << time[i].stats[6] << ")";
        Info << "Stats: HP(" << time[i].stats[0] << ") ATK(" << time[i].stats[1] << ") DEF(" << time[i].stats[2] << ") SP.ATK(" << time[i].stats[3] << ") SP.DEF(" << time[i].stats[4] << ") SPE(" << time[i].stats[5] << ") Total(" << time[i].stats[6] << ")";
        Info << endl << "Possíveis habilidades: " << endl << time[i].hab ;
        cout << endl << "Possíveis habilidades: " << endl << time[i].hab;
        
        if(time[i].evolvl != -1 && time[i].final == 0){
            cout << endl << "Evolui para " << Dex[time[i].dex].nome << " no nível " << time[i].evolvl;
            Info << endl << "Evolui para " << Dex[time[i].dex].nome << " no nível " << time[i].evolvl;
        }else if(time[i].evolvl == -1 && time[i].final == 0){
            cout << endl << "Evolui com métodos especiais";
            Info << endl << "Evolui com métodos especiais";
        }
    if(i < 5){Info << endl << endl;}
    }
}

int main(){
    ifstream dados;
    ofstream Info;
    Pokemon* Dex = new Pokemon[151];
    Time* time = new Time[6];

    dados.open("pokedex.txt");
    Dex[0].Preencher(dados, Dex);
    dados.close();
    Dex[0].Exibir(Dex);
    time[0].Preencher(time, Dex);
    Info.open("Time.txt");
    time[0].Exibir(time, Dex, Info);
    Info.close();
    
    delete [] time;
    delete [] Dex;
    
    return 0;
}
