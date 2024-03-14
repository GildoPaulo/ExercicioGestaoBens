#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib> // Aqui importamos a biblioteca para usar a função system()

using namespace std;

// Definindo a estrutura para armazenar os dados das minhas coisas
struct Item {
    string nome; // Aqui guardo o nome do item
    string tipo; // Aqui guardo o tipo do item, como "propriedade" ou "pessoal"
    string dataAdquirido; // Aqui guardo a data em que adquiri o item
    float peso; // Aqui guardo o peso do item
    string localizacao; // Aqui guardo a localização do item, se for uma propriedade
};

// Função para ler os registros dos meus itens de um arquivo
vector<Item> lerItens() {
    vector<Item> itens; // Aqui vou guardar os itens
    ifstream arquivo("meus_itens.txt"); // Aqui abro o arquivo para leitura
    if (arquivo.is_open()) {
        Item item; // Aqui vou criar um novo item
        while (true) {
            // Leio os dados do arquivo e armazeno no item
            arquivo >> item.nome >> item.tipo >> item.dataAdquirido >> item.peso;
            // Verifico se o tipo é 'propriedade' para ler a localização
            if (item.tipo == "propriedade") {
                getline(arquivo, item.localizacao); // Leio a localização com espaços
            }
            itens.push_back(item); // Adiciono o item ao vetor
            if (arquivo.eof()) {
                break; // Saio do loop quando chegar ao final do arquivo
            }
        }
        arquivo.close(); // Aqui fecho o arquivo após a leitura
    } else {
        cout << "Nao consegui abrir o arquivo." << endl; // Exibo uma mensagem de erro se não conseguir abrir o arquivo
    }
    return itens; // Retorno o vetor de itens
}

// Função para escrever os registros dos meus itens em um arquivo
void escreverItens(const vector<Item>& itens) {
    ofstream arquivo("meus_itens.txt"); // Aqui abro o arquivo para escrita
    if (arquivo.is_open()) {
        // Percorro o vetor de itens
        for (int i = 0; i < itens.size(); ++i) {
            // Escrevo os dados do item no arquivo
            arquivo << itens[i].nome << " " << itens[i].tipo << " " << itens[i].dataAdquirido << " " << itens[i].peso;
            if (itens[i].tipo == "propriedade") {
                arquivo << " " << itens[i].localizacao; // Escrevo a localização se o tipo for 'propriedade'
            }
            arquivo << endl;
        }
        arquivo.close(); // Aqui fecho o arquivo após a escrita
    } else {
        cout << "Nao consegui abrir o arquivo para escrita." << endl; // Exibo uma mensagem de erro se não conseguir abrir o arquivo
    }
}

// Função para adicionar um novo item ao vetor de itens
void adicionarItem(vector<Item>& itens) {
    Item novoItem; // Aqui crio um novo item
    // Peço e leio os dados do novo item do usuário
    cout << "Digite o nome do item: ";
    getline(cin, novoItem.nome); // Leio o nome do item com espaços
    cout << "Digite o tipo do item: ";
    cin >> novoItem.tipo;
    cout << "Digite a data de aquisicao do item: ";
    cin >> novoItem.dataAdquirido;
    cout << "Digite o peso do item: ";
    cin >> novoItem.peso;
    cin.ignore(); // Limpo o buffer do teclado
    if (novoItem.tipo == "propriedade") {
        cout << "Digite a localizacao do item: ";
        getline(cin, novoItem.localizacao); // Leio a localização do item com espaços
    }
    itens.push_back(novoItem); // Adiciono o novo item ao vetor
}

// Função para editar um item existente
void editarItem(vector<Item>& itens) {
    string nomeItem;
    cout << "Digite o nome do item que deseja editar: ";
    getline(cin, nomeItem); // Leio o nome do item com espaços
    // Percorro o vetor de itens
    for (int i = 0; i < itens.size(); ++i) {
        // Verifico se o nome do item corresponde ao informado pelo usuário
        if (itens[i].nome == nomeItem) {
            // Peço e leio os novos dados do item do usuário
            cout << "Digite o novo nome do item: ";
            getline(cin, itens[i].nome); // Leio o nome do item com espaços
            cout << "Digite o novo tipo do item: ";
            cin >> itens[i].tipo;
            cout << "Digite a nova data de aquisicao do item: ";
            cin >> itens[i].dataAdquirido;
            cout << "Digite o novo peso do item: ";
            cin >> itens[i].peso;
            cin.ignore(); // Limpo o buffer do teclado
            if (itens[i].tipo == "propriedade") {
                cout << "Digite a nova localizacao do item: ";
                getline(cin, itens[i].localizacao); // Leio a localização do item com espaços
            }
            cout << "Item editado com sucesso." << endl; // Exibo uma mensagem de sucesso
            return;
        }
    }
    cout << "Item nao encontrado." << endl; // Exibo uma mensagem de erro se o item não for encontrado
}

// Função para excluir um item existente
void excluirItem(vector<Item>& itens) {
    string nomeItem;
    cout << "Digite o nome do item que deseja excluir: ";
    getline(cin, nomeItem); // Leio o nome do item com espaços
    // Percorro o vetor de itens
    for (int i = 0; i < itens.size(); ++i) {
        // Verifico se o nome do item corresponde ao informado pelo usuário
        if (itens[i].nome == nomeItem) {
            itens.erase(itens.begin() + i); // Removo o item do vetor
            cout << "Item excluído com sucesso." << endl; // Exibo uma mensagem de sucesso
            return;
        }
    }
    cout << "Item nao encontrado." << endl; // Exibo uma mensagem de erro se o item não for encontrado
}

// Função para pesquisar itens por nome
void pesquisarPorNome(const vector<Item>& itens) {
    string nomeItem;
    cout << "Digite o nome do item que deseja pesquisar: ";
    getline(cin, nomeItem); // Leio o nome do item com espaços
    // Percorro o vetor de itens
    for (int i = 0; i < itens.size(); ++i) {
        // Verifico se o nome do item corresponde ao informado pelo usuário
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
    cout << "Item não encontrado." << endl; // Exibo uma mensagem de erro se o item não for encontrado
}

// Função para exibir os itens cadastrados
void exibirItens(const vector<Item>& itens) {
    if (itens.empty()) {
        cout << "Nenhum item cadastrado." << endl; // Exibo uma mensagem se não houver itens cadastrados
    } else {
        cout << "Itens cadastrados:" << endl;
        // Percorro o vetor de itens
        for (int i = 0; i < itens.size(); ++i) {
            // Exibo os dados de cada item cadastrado
            cout << "Nome: " << itens[i].nome << ", Tipo: " << itens[i].tipo
                 << ", Data de Aquisição: " << itens[i].dataAdquirido << ", Peso: " << itens[i].peso;
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

        // Exibo o menu de opções para o usuário
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

        // Realizo a ação correspondente à opção escolhida pelo usuário
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
                cout << "Opcao inválida. Por favor, escolha uma opcao valida." << endl;
        }

        cout << "\nPressione Enter para continuar...";
        cin.ignore(); // Aguardo a entrada do usuário para continuar
    } while (opcao != 6); // Continuo exibindo o menu até que o usuário escolha sair

    return 0;
}

