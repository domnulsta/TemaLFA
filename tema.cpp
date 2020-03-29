#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
using namespace std;
char a[100][100][30],w[20];//a=matricea de adiacenta pentru automat , exista tranzitie de la starea i la coloana j daca a[i][j] nu este "\0"
//w este cuvantul pe care il verifica
int n,init,nrstf,finale[100];
//n=nr. de stari, init=starea initiala, nrstf=nr. stari finale, finale=vectorul starilor finale ,
ifstream f("stari.in");
/*structura datelor de citire in fisier este:
n
init
nrstf
nrstf de stari finale
w
pe restul liniilor sunt tranzitiile:qi qj string
se face tranzitia din qi in qj prin literele din string
*/
queue<int> q1, q2;//vom folosi doua cozi pentru parcurgerea pas cu pas a cuvantului , se vor salva starile starile care pot trece la pasul urmator
void citire()
{
	int x, y, i;
	f >> n >> init >> nrstf;
	for (i = 0; i < nrstf; ++i)
		f >> finale[i];
	f>>w;
	while (f >> x >> y)
		f >> a[x][y];
}
int main()
{
	citire();
	int i, j, k;
	q1.push(init);//se adauga starea initiala in q1
	for (i = 0; i < strlen(w) && (!q1.empty()); ++i)//se parcurge tot cuvantul , litera cu litera , pana la final ori pana nu se mai poate parcurge(adica daca nu exista continuari)
	{
		while (!q1.empty())//pentru pasul i , se iau toate variantele posibile , stocate in q1(ca stari)
		{
			for (j = 0; j < n; ++j)
            {
				if (strchr(a[q1.front()][j], w[i]) != NULL)
					{q2.push(j);}
            }//se adauga in q2 orice stare prin care are o tranzitie din starea actuala(q1.front()) prin w[i]
			q1.pop();//se trece la urmatoarea stare si se repeta procesul pentru tot pasul i
		}
		while (!q2.empty())//odata vidat q1 , se trec noile elemnte in q1 din q2 , iar q2 se videaza pentru a repeta pentru urmatorul pas
		{

			if (i == strlen(w)-1)//in acelasi timp , daca am parcurs tot cuvantul
				for (k = 0; k < nrstf; ++k)//si daca in q2 se gaseste o stare finala
					if (q2.front() == finale[k])
					{
						cout << "DA";//cuvantul este acceptat
						return 0;
					}
            q1.push(q2.front());
			q2.pop();
		}
	}
	cout<<"NU";//daca s-a trecut prin tot cuvantul si nu a fost acceptat un cuvant , inseamna ca acesta nu este acceptat si se afiseaza mesajul "NU"
	return 0;
}
