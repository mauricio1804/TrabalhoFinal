#include <iostream>
#include <iomanip>
#include <assert.h>
using namespace std;

typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct
{
    int id;
    string nome;
    double preco;
    Data lancamento;
    string descricao;
} Jogos;

int addjoguin(Jogos *jogos)
{
    cout << "ID: ";
    cin >> jogos->id;
    cout << "Nome: ";
    cin.ignore();
    getline(cin, jogos->nome);
    cout << "Preco: ";
    cin >> jogos->preco;
    cout << "Data de lancamento (somente com espacos): ";
    cin >> jogos->lancamento.dia >> jogos->lancamento.mes >> jogos->lancamento.ano;
    cout << "Descricao: ";
    cin.ignore();
    getline(cin, jogos->descricao);

    return 1;
}

// teste
void teste(Jogos *jogos)
{
    assert(jogos->id > 0 && "O ID deve ser um valor positivo");
}

// colocar jogos predefinidos
Jogos gamesprontos(int id, string nome, double preco, int dia, int mes, int ano, string descriao)
{
    Jogos jogo;
    jogo.id = id;
    jogo.nome = nome;
    jogo.preco = preco;
    jogo.lancamento.dia = dia;
    jogo.lancamento.mes = mes;
    jogo.lancamento.ano = ano;
    jogo.descricao = descriao;
    return jogo;
}

// imprime os jogos
void imprimeJogo(Jogos *games)
{

    cout << "Jogo Novo" << endl;
    cout << "ID: " << games->id << endl;
    cout << "Nome: " << games->nome << endl;
    cout << fixed << setprecision(2)<< "Preco: R$" << games->preco << endl;
    cout << "Data de lancamento: " << games->lancamento.dia << "/" << games->lancamento.mes << "/" << games->lancamento.ano << endl;
    cout << "Descricao: " << games->descricao << endl;
}

// busca jogos
void buscar_jogo(int x, Jogos *v, int inicio, int fim)
{
    if (inicio > fim)
        cout << "Nao encontrado" << endl;
    else
    {
        int meio = (inicio + fim) / 2;
        if (x == v[meio].id)
            imprimeJogo(&v[meio]);
        else if (x < v[meio].id)
            buscar_jogo(x, v, inicio, meio - 1);
        else
            buscar_jogo(x, v, meio + 1, fim);
    }
}

// preenche jogos
int preencheListajogos(Jogos *vetor, int i)
{
    char resposta;
    do
    {
        i += addjoguin(&vetor[i]);
        cout << "Deseja adicionar um novo jogo? (s/n)" << endl;

    } while (((cin >> resposta) && ((resposta == 'S') || (resposta == 's'))));

    return i;
}

void ordenaListajogos(Jogos *v, int n)
{
    int i, j;
    Jogos aux;
    for (i = 1; i < n; i++)
    {
        j = i - 1;
        aux = v[i];
        while (j >= 0 && aux.id < v[j].id)
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = aux;
    }
}

void deleta_jogo(int x, Jogos *v, int n)
{
    int pos = 0;
    for (int i = 0; i < n; i++)
    {
        if (v[i].id == x)
        {
            pos = i;
        }
    }
    for (int i = pos + 1; i < n; ++i)
    {
        v[i - 1] = v[i];
    }
}

int main()
{
    Jogos jogonovo[1000];
    Jogos game1, game2, game3, game4, game5;
    int N = 5, escolha, id_delet;

    game1 = gamesprontos(00, "Batman Arkham Knight", 89.99, 23, 06, 2015, "Batman: Arkham Knight eh um jogo eletronico de açao-aventura produzido pela Rocksteady Studios");
    game2 = gamesprontos(12, "Minecraft", 79.90, 18, 11, 2011, "Minecraft eh um jogo eletronico sandbox de sobrevivencia ");
    game3 = gamesprontos(02, "Subway Surf", 0.00, 24, 05, 2012, "Subway Surfers eh um jogo eletronico de corrida interminavel co-desenvolvido pela Kiloo Games");
    game4 = gamesprontos(06, "Until Dawn", 29.90, 26, 07, 2015, "Until Dawn eh um jogo eletronico de aventura e de survival horror desenvolvido pela Supermassive");
    game5 = gamesprontos(04, "Red Dead Redemption 2", 50.00, 26, 11, 2018, "Roubaram nosso GOTY");

    jogonovo[0] = game1;
    jogonovo[1] = game2;
    jogonovo[2] = game3;
    jogonovo[3] = game4;
    jogonovo[4] = game5;

    do
    {
        cout << "digite 1 para cadastrar novo jogo" << endl;
        cout << "digite 2 para listar jogos" << endl;
        cout << "digite 3 para buscar jogo pelo ID" << endl;
        cout << "digite 4 para remover jogo" << endl;
        cout << "digite 0 para terminar a execucao" << endl;
        cin >> escolha;

        switch (escolha)
        {
        case 1:
            system("cls");
            N = preencheListajogos(jogonovo, N);

            break;
        case 2:
            system("cls");
            ordenaListajogos(jogonovo, N);
            Jogos *p, *u;
            p = &jogonovo[0];
            u = &jogonovo[N - 1];
            while (p <= u)
            {
                imprimeJogo(p);
                cout << endl;
                p++;
            }

            break;
        case 3:
            system("cls");
            ordenaListajogos(jogonovo, N);
            int *x;
            if (!(x = new (nothrow) int[N]))
            {
                cout << "Falha de alocacao de memoria" << endl;
                return -1;
            }
            cout << "Informe o ID para a busca: " << endl;
            cin >> *x;
            buscar_jogo(*x, jogonovo, 0, N);
            delete x;
            x = NULL;

            break;
        case 4:
            system("cls");
            cout << "Informe o ID do jogo que deseja deletar: " << endl;
            cin >> id_delet;
            deleta_jogo(id_delet, jogonovo, N);
            N--;

            break;

        default:
            break;
        }
    } while (escolha != 0);

    return 0;
}