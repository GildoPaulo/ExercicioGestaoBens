#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib> // Aqui importamos a biblioteca para usar a fun��o system()

using namespace std;

// Definindo a estrutura para armazenar os dados das minhas coisas
struct Item {
    string nome; // Aqui guardo o nome do item
    string tipo; // Aqui guardo o tipo do item, como "propriedade" ou "pessoal"
    string dataAdquirido; // Aqui guardo a data em que adquiri o item
    float peso; // Aqui guardo o peso do item
    string localizacao; // Aqui guardo a localiza��o do item, se for uma propriedade
};

// Fun��o para ler os registros dos meus itens de um arquivo
vector<Item> lerItens() {
    vector<Item> itens; // Aqui vou guardar os itens
    ifstream arquivo("meus_itens.txt"); // Aqui abro o arquivo para leitura
    if (arquivo.is_open()) {
        Item item; // Aqui vou criar um novo item
        while (true) {
            // Leio os dados do arquivo e armazeno no item
            arquivo >> item.nome >> item.tipo >> item.dataAdquirido >> item.peso;
            // Verifico se o tipo � 'propriedade' para ler a localiza��o
            if (item.tipo == "propriedade") {
                getline(arquivo, item.localizacao); // Leio a localiza��o com espa�os
            }
            itens.push_back(item); // Adiciono o item ao vetor
            if (arquivo.eof()) {
                break; // Saio do loop quando chegar ao final do arquivo
            }
        }
        arquivo.close(); // Aqui fecho o arquivo ap�s a leitura
    } else {
        cout << "Nao consegui abrir o arquivo." << endl; // Exibo uma mensagem de erro se n�o conseguir abrir o arquivo
    }
    return itens; // Retorno o vetor de itens
}

// Fun��o para escrever os registros dos meus itens em um arquivo
void escreverItens(const vector<Item>& itens) {
    ofstream arquivo("meus_itens.txt"); // Aqui abro o arquivo para escrita
    if (arquivo.is_open()) {
        // Percorro o vetor de itens
        for (int i = 0; i < itens.size(); ++i) {
            // Escrevo os dados do item no arquivo
            arquivo << itens[i].nome << " " << itens[i].tipo << " " << itens[i].dataAdquirido << " " << itens[i].peso;
            if (itens[i].tipo == "propriedade") {
                arquivo << " " << itens[i].localizacao; // Escrevo a localiza��o se o tipo for 'propriedade'
            }
            arquivo << endl;
        }
        arquivo.close(); // Aqui fecho o arquivo ap�s a escrita
    } else {
        cout << "Nao consegui abrir o arquivo para escrita." << endl; // Exibo uma mensagem de erro se n�o conseguir abrir o arquivo
    }
}

// Fun��o para adicionar um novo item ao vetor de itens
void adicionarItem(vector<Item>& itens) {
    Item novoItem; // Aqui crio um novo item
    // Pe�o e leio os dados do novo item do usu�rio
    cout << "Digite o nome do item: ";
    getline(cin, novoItem.nome); // Leio o nome do item com espa�os
    cout << "Digite o tipo do item: ";
    cin >> novoItem.tipo;
    cout << "Digite a data de aquisicao do item: ";
    cin >> novoItem.dataAdquirido;
    cout << "Digite o peso do item: ";
    cin >> novoItem.peso;
    cin.ignore(); // Limpo o buffer do teclado
    if (novoItem.tipo == "propriedade") {
        cout << "Digite a localizacao do item: ";
        getline(cin, novoItem.localizacao); // Leio a localiza��o do item com espa�os
    }
    itens.push_back(novoItem); // Adiciono o novo item ao vetor
}

// Fun��o para editar um item existente
void editarItem(vector<Item>& itens) {
    string nomeItem;
    cout << "Digite o nome do item que deseja editar: ";
    getline(cin, nomeItem); // Leio o nome do item com espa�os
    // Percorro o vetor de itens
    for (int i = 0; i < itens.size(); ++i) {
        // Verifico se o nome do item corresponde ao informado pelo usu�rio
        if (itens[i].nome == nomeItem) {
            // Pe�o e leio os novos dados do item do usu�rio
            cout << "Digite o novo nome do item: ";
            getline(cin, itens[i].nome); // Leio o nome do item com espa�os
            cout << "Digite o novo tipo do item: ";
            cin >> itens[i].tipo;
            cout << "Digite a nova data de aquisicao do item: ";
            cin >> itens[i].dataAdquirido;
            cout << "Digite o novo peso do item: ";
            cin >> itens[i].peso;
            cin.ignore(); // Limpo o buffer do teclado
            if (itens[i].tipo == "propriedade") {
                cout << "Digite a nova localizacao do item: ";
                getline(cin, itens[i].localizacao); // Leio a localiza��o do item com espa�os
            }
            cout << "Item editado com sucesso." << endl; // Exibo uma mensagem de sucesso
            return;
        }
    }
    cout << "Item nao encontrado." << endl; // Exibo uma mensagem de erro se o item n�o for encontrado
}

// Fun��o para excluir um item existente
void excluirItem(vector<Item>& itens) {
    string nomeItem;
    cout << "Digite o nome do item que deseja excluir: ";
    getline(cin, nomeItem); // Leio o nome do item com espa�os
    // Percorro o vetor de itens
    for (int i = 0; i < itens.size(); ++i) {
        // Verifico se o nome do item corresponde ao informado pelo usu�rio
        if (itens[i].nome == nomeItem) {
            itens.erase(itens.begin() + i); // Removo o item do vetor
            cout << "Item exclu�do com sucesso." << endl; // Exibo uma mensagem de sucesso
            return;
        }
    }
    cout << "Item nao encontrado." << endl; // Exibo uma mensagem de erro se o item n�o for encontrado
}

// Fun��o para pesquisar itens por nome
void pesquisarPorNome(const vector<Item>& itens) {
    string nomeItem;
    cout << "Digite o nome do item que deseja pesquisar: ";
    getline(cin, nomeItem); // Leio o nome do item com espa�os
    // Percorro o vetor de itens
    for (int i = 0; i < itens.size(); ++i) {
        // Verifico se o nome do item corresponde ao informado pelo usu�rio
        if (itens[i].nome == nomeItem) {
            // Exibo os dados do item encontrado
            cout << "Item encontrado:" << endl;
            cout << "Nome: " << itens[i].nome << ", Tipo: " << itens[i].tipo
                 << ", Data de Aquisicao: " << itens[i].dataAdquirido << ", Peso: " << itens[i].peso;
            if (itens[i].tipo == "propriedade") {
                cout << ", Localizacao: " << itens[i].localizacao;
            }
            cout << endl;
            return;
        }
    }
    cout << "Item n�o encontrado." << endl; // Exibo uma mensagem de erro se o item n�o for encontrado
}

// Fun��o para exibir os itens cadastrados
void exibirItens(const vector<Item>& itens) {
    if (itens.empty()) {
        cout << "Nenhum item cadastrado." << endl; // Exibo uma mensagem se n�o houver itens cadastrados
    } else {
        cout << "Itens cadastrados:" << endl;
        // Percorro o vetor de itens
        for (int i = 0; i < itens.size(); ++i) {
            // Exibo os dados de cada item cadastrado
            cout << "Nome: " << itens[i].nome << ", Tipo: " << itens[i].tipo
                 << ", Data de Aquisi��o: " << itens[i].dataAdquirido << ", Peso: " << itens[i].peso;
            if (itens[i].tipo == "propriedade") {
                cout << ", Localizacao: " << itens[i].localizacao;
            }
            cout << endl;
        }
    }
}

int main() {
    vector<Item> itens = lerItens(); // Aqui leio os registros de itens do arquivo
    int opcao;
    do {
        system("cls"); // Limpo a tela

        // Exibo o menu de op��es para o usu�rio
        cout << "\nMenu de Opcoes:" << endl;
        cout << "1. Adicionar novo item" << endl;
        cout << "2. Editar item existente" << endl;
        cout << "3. Excluir item existente" << endl;
        cout << "4. Pesquisar item por nome" << endl;
        cout << "5. Exibir itens cadastrados" << endl;
        cout << "6. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore(); // Limpo o buffer do teclado

        // Realizo a a��o correspondente � op��o escolhida pelo usu�rio
        switch (opcao) {
            case 1:
                system("cls");
                adicionarItem(itens);
                break;
            case 2:
                system("cls");
                editarItem(itens);
                break;
            case 3:
                system("cls");
                excluirItem(itens);
                break;
            case 4:
                system("cls");
                pesquisarPorNome(itens);
                break;
            case 5:
                system("cls");
                exibirItens(itens);
                break;
            case 6:
                system("cls");
                escreverItens(itens); // Aqui escrevo os registros de itens no arquivo
                cout << "Programa encerrado." << endl;
                break;
            default:
                cout << "Opcao inv�lida. Por favor, escolha uma opcao valida." << endl;
        }

        cout << "\nPressione Enter para continuar...";
        cin.ignore(); // Aguardo a entrada do usu�rio para continuar
    } while (opcao != 6); // Continuo exibindo o menu at� que o usu�rio escolha sair

    return 0;
}

