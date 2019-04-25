#include <iostream>
#include <fstream>

using namespace std;

#include <vector>

#include "Personagem.h"
#include "Helicoptero.h"
#include "Veiculo.h"
#include "Imovel.h"
#include "DoisCaraNumaMoto.h"

vector<Objeto*> objetos;
vector<Camera*> cameras;

int posSelecionado = -1;
int posCam = -1;

void salvaCenario()
{
    ofstream file_obj("../save/salvo.txt");

    file_obj << objetos.size() << '\n';
    for(auto obj: objetos){
       file_obj << obj->tipo << '\n';
       file_obj << obj->t.x << '\n' << obj->t.y << '\n' << obj->t.z << '\n';
       file_obj << obj->a.x << '\n' << obj->a.y << '\n' << obj->a.z << '\n';
       file_obj << obj->s.x << '\n' << obj->s.y << '\n' << obj->s.z << '\n';
    }
}

void carregaCenario(string arquivo) {
    ifstream file_obj(arquivo);

    string atual;
    getline(file_obj, atual);
    int n = strtof(atual.c_str(),0);

    int tipo;
    float t[3], a[3], s[3];
    for(int i = 0; i < n; i++)
    {
        getline(file_obj, atual);
        tipo = strtof(atual.c_str(),0);
        getline(file_obj, atual);
        t[0] = strtof(atual.c_str(),0);
        getline(file_obj, atual);
        t[1] = strtof(atual.c_str(),0);
        getline(file_obj, atual);
        t[2] = strtof(atual.c_str(),0);
        getline(file_obj, atual);
        a[0] = strtof(atual.c_str(),0);
        getline(file_obj, atual);
        a[1] = strtof(atual.c_str(),0);
        getline(file_obj, atual);
        a[2] = strtof(atual.c_str(),0);
        getline(file_obj, atual);
        s[0] = strtof(atual.c_str(),0);
        getline(file_obj, atual);
        s[1] = strtof(atual.c_str(),0);
        getline(file_obj, atual);
        s[2] = strtof(atual.c_str(),0);

        switch (tipo) {
        case PERSONAGEM:
            objetos.push_back( new Personagem() );
            break;

        case HELICOPTERO:
            objetos.push_back( new Helicoptero() );
            break;

        case CARRO1:
            objetos.push_back( new Veiculo(CARRO1) );
            break;

        case CARRO2:
            objetos.push_back( new Veiculo(CARRO2) );
            break;

        case MOTO:
            objetos.push_back( new Veiculo(MOTO) );
            break;

        case BICICLETA:
            objetos.push_back( new Veiculo(BICICLETA) );
            break;

        case IMOVEL1:
            objetos.push_back( new Imovel(IMOVEL1) );
            break;

        case IMOVEL2:
            objetos.push_back( new Imovel(IMOVEL2) );
            break;

        case CARASMOTO:
            objetos.push_back( new DoisCaraNumaMoto());
            break;

        default:
            break;
        }
        objetos[i]->t = Vetor3D(t[0], t[1], t[2]);
        objetos[i]->a = Vetor3D(a[0], a[1], a[2]);
        objetos[i]->s = Vetor3D(s[0], s[1], s[2]);
    }
}

void desenha() {
    GUI::displayInit();


    GUI::setLight(0,10,10,10,true,false);
    GUI::setLight(1,-10,10,-10,true,false);


    GUI::drawOrigin(1);

    GUI::setColor(0,1,0);
    GUI::drawFloor(10, 10);

    for (int i = 0; i < objetos.size(); ++i) {
        glPushMatrix();
            objetos[i]->atualiza(5);
            objetos[i]->desenha();
        glPopMatrix();
    }

    if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
        objetos[posSelecionado]->t.x += glutGUI::dtx;
        objetos[posSelecionado]->t.y += glutGUI::dty;
        objetos[posSelecionado]->t.z += glutGUI::dtz;

        objetos[posSelecionado]->a.x += glutGUI::dax;
        objetos[posSelecionado]->a.y += glutGUI::day;
        objetos[posSelecionado]->a.z += glutGUI::daz;

        objetos[posSelecionado]->s.x += glutGUI::dsx;
        objetos[posSelecionado]->s.y += glutGUI::dsy;
        objetos[posSelecionado]->s.z += glutGUI::dsz;
    }

    GUI::displayEnd();
}

bool incluirObjeto = false;

void teclado(unsigned char key, int x, int y) {
    //if (!incluirObjeto) {
        GUI::keyInit(key,x,y);
    //}

    switch (key) {
    case 't':
        glutGUI::trans_obj = !glutGUI::trans_obj;
        break;
    case 'l':
        glutGUI::trans_luz = !glutGUI::trans_luz;
        break;

    case 'k':
        if(posSelecionado >= 0 and posSelecionado < objetos.size())
        {
            objetos[posSelecionado]->origem = !objetos[posSelecionado]->origem;
        }
        break;

    case 'n':
        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos[posSelecionado]->selecionado = false;
        }
        posSelecionado++;
        if (posSelecionado >= objetos.size()) {
            posSelecionado = 0;
        }
        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos[posSelecionado]->selecionado = true;
        }
        break;

    case 'b':
        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos[posSelecionado]->selecionado = false;
        }
        posSelecionado--;
        if (posSelecionado < 0) {
            posSelecionado = objetos.size()-1;
        }
        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos[posSelecionado]->selecionado = true;
        }
        break;

    case 'O':
        incluirObjeto = !incluirObjeto;
        break;

    case 'p':
        if (incluirObjeto) {
            objetos.push_back( new Personagem() );
        }
        break;

    case 'h':
        if (incluirObjeto) {
            objetos.push_back( new Helicoptero() );
        }
        break;

    case 'v':
        if (incluirObjeto) {
            objetos.push_back( new Veiculo(CARRO1) );
        }
        break;

    case 'V':
        if (incluirObjeto) {
            objetos.push_back( new Veiculo(CARRO2) );
        }
        break;

    case 'g':
        if (incluirObjeto) {
            objetos.push_back( new Veiculo(MOTO) );
        }
        break;

    case 'G':
        if (incluirObjeto) {
            objetos.push_back( new Veiculo(BICICLETA) );
        }
        break;

    case 'i':
        if (incluirObjeto) {
            objetos.push_back( new Imovel(IMOVEL1) );
        }
        break;

    case 'I':
        if (incluirObjeto) {
            objetos.push_back( new Imovel(IMOVEL2) );
        }
        break;

    case 'a':
        if(incluirObjeto) {
            objetos.push_back( new DoisCaraNumaMoto());
        }
        break;

    case 'd':
        if(posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos.erase(objetos.begin() + posSelecionado, objetos.begin() + posSelecionado + 1);
        }
        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos[posSelecionado]->selecionado = true;
        }
        break;

    case 'D':
        if(!objetos.empty())
            objetos.pop_back();
        break;

    case 'q':
        if(posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos[posSelecionado]->camera();
        }
        break;

    case 'Q':
        glutGUI::cam = new CameraDistante(Vetor3D(0, 10, 15), Vetor3D(0, 0, 0), Vetor3D(0, 1, 0));
        break;

    case 'e':
        posCam++;
        if (posCam >= cameras.size()) {
            posCam = 0;
        }
        glutGUI::cam = new CameraDistante(cameras[posCam]->e, cameras[posCam]->c, cameras[posCam]->u);
        break;

    case 'E':
        glutGUI::cam = new CameraDistante(Vetor3D(0, 10, 15), Vetor3D(0, 0, 0), Vetor3D(0, 1, 0));
        break;

    case 'S':
        salvaCenario();
        break;

    default:
        break;
    }
}

void instrucoes()
{
    cout << "Teclas para adicionar objetos" << endl;
    cout << " 'i' : Imovel 1" << endl;
    cout << " 'I' : Imovel 2" << endl;
    cout << " 'v' : Veiculo 1" << endl;
    cout << " 'V' : Veiculo 2" << endl;
    cout << " 'g' : Moto" << endl;
    cout << " 'G' : Bicicleta" << endl;
    cout << " 'p' : Personagem" << endl;
    cout << " 'h' : Helicoptero" << endl;
    cout << " 'a' : 2 caras numa moto" << endl;
    cout << endl;
    cout << "'n' para selecionar proximo, 'b' para selecionar anterior" << endl;
    cout << "O objeto selecionado exibira um circulo vermelho em baixo de si" << endl;
    cout << "Se um personagem ou helicoptero estiver selecionado, 'q' para mudar a camera" << endl;
    cout << "Para as cameras alternativas, 'e'" << endl;
    cout << "'Q' ou 'E' para voltar a camera padrao" << endl;
    cout << "'S' para salvar o cenario atual" << endl;
    cout << "Digite 1 para carregar o cenário modelado, 2 para um cenário salvo" << endl;
    cout << "qualquer outro para um cenário novo" << endl;
    cout << "-> ";
    int op;
    cin >> op;
    switch (op) {
    case 1:
        carregaCenario("../save/cenario.txt");
        break;

    case 2:
        carregaCenario("../save/salvo.txt");
        break;

    default:
        break;
    }
}

int main()
{
    cameras.push_back(new CameraDistante(Vetor3D(0, 20, 0.1), Vetor3D(0, 0, 0), Vetor3D(0, 1, 0)));
    cameras.push_back(new CameraDistante(Vetor3D(20, 5, 5), Vetor3D(0, 0, 0), Vetor3D(0, 1, 0)));
    cameras.push_back(new CameraDistante(Vetor3D(10, 5, 20), Vetor3D(0, 0, 0), Vetor3D(0, -1, 0)));

    instrucoes();

    glutGUI::cam = new CameraDistante(Vetor3D(0, 10, 15), Vetor3D(0, 0, 0), Vetor3D(0, 1, 0));

    GUI gui = GUI(800,600,desenha,teclado);
}