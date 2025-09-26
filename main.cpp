#include <iostream>
#include <fstream>

using namespace std;

struct horario
{
public:
    int hora, min, seg;
    int *ptr = &hora;
};

int FazerOp(char op, int x, int y)
{
    switch (op)
    {
    case '+':
        x = x + y;
        break;
    case '-':
        x = x - y;
        break;
    case 'x':
        x = x * y;
        break;
    case 'X':
        x = x * y;
        break;
    case '/':
        x = x / y;
        break;
    default:
        cout << "Operacao invalida!";
        break;
    }
    return x;
}

void ParaSeg(int *x)
{
    *(x + 2) = (*(x + 0) * 3600) + (*(x + 1) * 60) + *(x + 2);
    *(x + 0) = 0;
    *(x + 1) = 0;
}

void ParaHoras(int *x)
{
    *(x + 1) = *(x + 2) / 60;
    *(x + 2) = *(x + 2) % 60;
    *(x + 0) = *(x + 1) / 60;
    *(x + 1) = *(x + 1) % 60;
}

void ImprimirSalvar(ostream &arq1, int z)
{
    if (z == 0)
    {
        cout << "00";
        arq1 << 00;
    }
    else if (z < 10)
    {
        cout << "0" << z;
        arq1 << 0 << z;
    }
    else
    {
        cout << z;
        arq1 << z;
    }
}

void Imprimir(int z)
{
    if (z == 0)
    {
        cout << "00";
    }
    else if (z < 10)
    {
        cout << "0" << z;
    }
    else
    {
        cout << z;
    }
}

int main()
{
    while (1)
    {

        int horas1[3] = {0, 0, 0}, horas2[3] = {0, 0, 0}, result[3] = {0, 0, 0};
        int *ptr1 = &horas1[0], *ptr2 = horas2, *ptr3 = result;
        char op;

        cout << "======================================================================\n\nDigite o primeiro horario: (HH MM SS) ou '0 0 0' para encerrar;\n";
        cin >> horas1[0] >> horas1[1] >> horas1[2];
        if (horas1[0] + horas1[1] + horas1[2] == 0)
        {
            break;
        }

        cout << "Qual a operacao? ( +, -, x, /)\n";
        cin >> op;

        if ((op == '+') || (op == '-'))
        {
            cout << "Digite o segundo horario: (HH MM SS)\n";
            cin >> horas2[0] >> horas2[1] >> horas2[2];
        }
        else
        {
            cout << "Digite o valor: ";
            cin >> horas2[2];
            if ((horas2[2] == 0) && op == '/')
            {
                cout << "Divisao por 0 nao eh possivel, reiniciando...\n\n";
                continue;
            }
        }
        cout << endl;
        Imprimir(horas1[0]);
        cout << ":";
        Imprimir(horas1[1]);
        cout << ":";
        Imprimir(horas1[2]);
        cout << " " << op << " ";

        if ((op == '+') || (op == '-'))
        {
            Imprimir(horas2[0]);
            cout << ":";
            Imprimir(horas2[1]);
            cout << ":";
            Imprimir(horas2[2]);

            ParaSeg(ptr2);
        }
        else
        {
            cout << horas2[2];
        }

        ParaSeg(ptr1);

        result[2] = FazerOp(op, horas1[2], horas2[2]);
        ParaHoras(ptr3);

        cout << " = ";
        ofstream arq("arquivo_horas.txt", ios::app);
        ImprimirSalvar(arq, result[0]);
        cout << ":";
        arq << ":";
        ImprimirSalvar(arq, result[1]);
        cout << ":";
        arq << ":";
        ImprimirSalvar(arq, result[2]);
        cout << endl;
        arq << endl;
        arq.close();

        if((result[1]==0)&&(result[2]==0)&&(result[0]!=0)){
            cout << "parabeins, horario irado, sla";
        }

        cout << endl << endl;
    }
    return 0;
}