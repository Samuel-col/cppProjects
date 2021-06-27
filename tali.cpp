#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;

// Herramientas ----------------------------

bool isIn(int arr[5],int num){
    //
    bool is;
    is=(
	(num==arr[0])||
	(num==arr[1])||
	(num==arr[2])||
	(num==arr[3])||
	(num==arr[4])
	);
    return is;
}

int sorter(int arr[5]){
    //
    int a;
    if(arr[0]>arr[1]){
	a=arr[1];
	arr[1]=arr[0];
	arr[0]=a;
    };
    if(arr[2]>arr[3]){
	a=arr[3];
	arr[3]=arr[2];
	arr[2]=a;
    };
    if(arr[1]>arr[2]){
	a=arr[2];
	arr[2]=arr[1];
	arr[1]=a;
    };
    if(arr[3]>arr[4]){
	a=arr[4];
	arr[4]=arr[3];
	arr[3]=a;
    };
    if(arr[0]>arr[1]){
	a=arr[1];
	arr[1]=arr[0];
	arr[0]=a;
    };
    if(arr[2]>arr[3]){
	a=arr[3];
	arr[3]=arr[2];
	arr[2]=a;
    };
    if(arr[1]>arr[2]){
	a=arr[2];
	arr[2]=arr[1];
	arr[1]=a;
    };
    if(arr[3]>arr[4]){
	a=arr[4];
	arr[4]=arr[3];
	arr[3]=a;
    };
    if(arr[0]>arr[1]){
	a=arr[1];
	arr[1]=arr[0];
	arr[0]=a;
    };
    if(arr[2]>arr[3]){
	a=arr[3];
	arr[3]=arr[2];
	arr[2]=a;
    }
    return 0;
}

int sum(int arr[5]){
    int s=0;
    for(int i=0;i<5;i++)
	s+=arr[i];
    return s;
}

int dado(){
    //
    return (rand()%6)+1;
}

// Juegos -----------------------------------
int totNum(int arr[5],int num){
    //
    int p=0;
    p+=(
	    (num==arr[0])+
	    (num==arr[1])+
	    (num==arr[2])+
	    (num==arr[3])+
	    (num==arr[4])
	);

    return p*num;
}

int bonif(int totSup){
    //
    return 35*(totSup>62);

}

int d3ig(int arr[5]){
    //
    return sum(arr)*(
	    ((arr[0]==arr[1])&&(arr[1]==arr[2]))
	    ||
	    ((arr[1]==arr[2])&&(arr[2]==arr[3]))
	    ||
	    ((arr[2]==arr[3])&&(arr[3]==arr[4]))
	    );
}

int d4ig(int arr[5]){
    //
    return sum(arr)*(
    ((arr[0]==arr[1])&&(arr[1]==arr[2])&&(arr[2]==arr[3]))
    ||
    ((arr[1]==arr[2])&&(arr[2]==arr[3])&&(arr[3]==arr[4]))
    );
}

int d5ig(int arr[5]){
    //
    return 50*(
	    (arr[0]==arr[1])&&
	    (arr[1]==arr[2])&&
	    (arr[2]==arr[3])&&
	    (arr[4]==arr[4])
	    );
}

int fullHouse(int arr[5]){
    //
    return 25*(
	    (
		(arr[0]==arr[1])&&
		(arr[2]==arr[3])&&
		(arr[3]==arr[4])&&
		(arr[0]!=arr[2])
	    )
	    ||
	    (
		(arr[0]==arr[1])&&
		(arr[1]==arr[2])&&
		(arr[3]==arr[4])&&
		(arr[0]!=arr[3])
	    )
	    );
}


int secCort(int arr[5]){
    //
    return 30*(
	    (isIn(arr,1) && isIn(arr,2) && isIn(arr,3) && isIn(arr,4))|| 
	    (isIn(arr,2) && isIn(arr,3) && isIn(arr,4) && isIn(arr,5))|| 
	    (isIn(arr,3) && isIn(arr,4) && isIn(arr,5) && isIn(arr,6)) 
	    );
}

int secCom(int arr[5]){
    //
    return 40*(
	    (isIn(arr,1) && isIn(arr,2) && isIn(arr,3) && isIn(arr,4)&&isIn(arr,5))|| 
	    (isIn(arr,2) && isIn(arr,2) && isIn(arr,4) && isIn(arr,5)&&isIn(arr,6)) 
	    );
}

int suerte(){
    //
    return rand()%25;
}
//------------------------------------

// Imprimir -------------------------

int printDados(int arr[5]){
    //
    cout << "_____________________" << endl;
    cout << "|_" << arr[0] << "_|_" << arr[1] << "_|_" << arr[2] << "_|_" << arr[3] << "_|_" << arr[4] << "_|" << endl;

    return 0;
}

int printSup(int tab[17],char disp[13]){
    //
    cout << "  | Juego:                Disp    Pts" << endl;
    cout << "a | Total de 1s:           " << disp[0] << "     " << tab[0] << endl;
    cout << "b | Total de 2s:           " << disp[1] << "     " << tab[1] << endl;
    cout << "c | Total de 3s:           " << disp[2] << "     " << tab[2] << endl;
    cout << "d | Total de 4s:           " << disp[3] << "     " << tab[3] << endl;
    cout << "e | Total de 5s:           " << disp[4] << "     " << tab[4] << endl;
    cout << "f | Total de 6s:           " << disp[5] << "     " << tab[5] << endl;
    cout << "Bonificación si >62:             " << tab[6] << endl;
    cout << "Total Superior:                  " << tab[7] << endl;
    cout << endl;
    cout << "g | 3 del Mismo Tipo:      " << disp[6] << "     " << tab[8] << endl;
    cout << "h | 4 del Mismo Tipo:      " << disp[7] << "     " << tab[9] << endl;
    cout << "i | Full House:            " << disp[8] << "     " << tab[10] << endl;
    cout << "j | Secuencia Corta:       " << disp[9] << "     " << tab[11] << endl;
    cout << "k | Secuencia Completa:    " << disp[10] << "     " << tab[12] << endl;
    cout << "l | 5 del Mismo Tipo:      " << disp[11] << "     " << tab[13] << endl;
    cout << "m | Suerte:                " << disp[12] << "     " << tab[14] << endl;
    cout << "Total Inferior:                  " << tab[15] << endl;
    cout << "____________________________________" << endl;
    cout << "Gran Total:                      " << tab[16] << endl;
    return 0;
}

// Checkeo ----------------------------

int check(int tab[17],int arr[5],char disp[13],char e,int rondas){
    switch (e){
	case 'a':
	    if (disp[0]=='n'){
		cout << "Ese juego ya había sido utilizado." << endl;
	    }else{
		tab[0]=totNum(arr,1);
		disp[0]='n';
	    };
	    break;
	case 'b':
	    if (disp[1]=='n'){
		cout << "Ese juego ya había sido utilizado." << endl;
	    }else{
		tab[1]=totNum(arr,2);
		disp[1]='n';
	    };
	    break;
	case 'c':
	    if (disp[2]=='n'){
		cout << "Ese juego ya había sido utilizado." << endl;
	    }else{
		tab[2]=totNum(arr,3);
		disp[2]='n';
	    };
	    break;
	case 'd':
	    if (disp[3]=='n'){
		cout << "Ese juego ya había sido utilizado." << endl;
	    }else{
		tab[3]=totNum(arr,4);
		disp[3]='n';
	    };
	    break;
	case 'e':
	    if (disp[4]=='n'){
		cout << "Ese juego ya había sido utilizado." << endl;
	    }else{
		tab[4]=totNum(arr,5);
		disp[4]='n';
	    };
	    break;
	case 'f':
	    if (disp[5]=='n'){
		cout << "Ese juego ya había sido utilizado." << endl;
	    }else{
		tab[5]=totNum(arr,6);
		disp[5]='n';
	    };
	    break;
	case 'g':
	    if (disp[6]=='n'){
		cout << "Ese juego ya había sido utilizado." << endl;
	    }else{
		tab[8]=d3ig(arr);
		disp[6]='n';
	    };
	    break;
	case 'h':
	    if (disp[7]=='n'){
		cout << "Ese juego ya había sido utilizado." << endl;
	    }else{
		tab[9]=d4ig(arr);
		disp[7]='n';
	    };
	    break;
	case 'i':
	    if (disp[8]=='n'){
		cout << "Ese juego ya había sido utilizado." << endl;
	    }else{
		tab[10]=fullHouse(arr);
		disp[8]='n';
	    };
	    break;
	case 'j':
	    if (disp[9]=='n'){
		cout << "Ese juego ya había sido utilizado." << endl;
	    }else{
		tab[11]=secCort(arr);
		disp[9]='n';
	    };
	    break;
	case 'k':
	    if (disp[10]=='n'){
		cout << "Ese juego ya había sido utilizado." << endl;
	    }else{
		tab[12]=secCom(arr);
		disp[10]='n';
	    };
	    break;
	case 'l':
	    if (disp[11]=='n'){
		cout << "Ya falló en este juego." << endl;
	    }else{
		tab[13]+=d5ig(arr);
		if(d5ig(arr)!=0){
		    rondas++;
		}else{
		    disp[11]=='n';
		};
	    };
	    break;
	case 'm':
	    if (disp[12]=='n'){
		cout << "Ese juego ya había sido utilizado." << endl;
	    }else{
		tab[14]=suerte();
		disp[12]='n';
	    };
	    break;
	default:
	    break;
    };

    tab[6]=bonif(tab[0]+tab[1]+tab[2]+tab[3]+tab[4]+tab[5]);
    tab[7]=tab[0]+tab[1]+tab[2]+tab[3]+tab[4]+tab[5]+tab[6];
    tab[15]=tab[8]+tab[9]+tab[10]+tab[11]+tab[12]+tab[13]+tab[14];
    tab[16]=tab[7]+tab[15];

    return --rondas;
}


//--------------------------------------

int main()
{
    //
    srand (time(NULL));
    int rondas=12;
    char disp[13];
    for (int i=0;i<13;i++)
				disp[i]='s';
    int tabla[17];
    for (int i=0;i<17;i++)
				tabla[i]=0;

    // while loop
    do{  	
  	
  	
  	

				cout << endl;
				cout << endl;
				cout << endl;
				cout << endl;
				cout << endl;

				int set[5];
				char e1;
				char e2;
				int lan=2;
				set[0]=dado();
  			set[1]=dado();
  			set[2]=dado();
  			set[3]=dado();
  			set[4]=dado();
				printDados(set);
				cout << endl;
				printSup(tabla,disp);
				cout << "¿Deseas seguir lanzando?(s/n) " << endl;
				cin >> e2;

				while ((e2=='s')&&(lan>0)){
				    lan--;
				    int rel;
				    cout << "¿Qué dados quieres volver a lanzar? " << endl;
				    cin >> rel;

				    for (int i=4;i>=0;i--){
					int ind;
					ind=rel/pow(10,i);
					if (ind!=0){
					    set[ind-1]=dado();
					    rel-=ind*pow(10,i);
					};
				    };

				    printDados(set);
				    cout << endl;
				    printSup(tabla,disp);
				    if (lan>0){
				    cout << "¿Deseas seguir lanzando?(s/n) " << endl;
				    cin >> e2;
				    };
				};

				cout << "¿Qué juego deseas utilizar?(a/b/.../l/m) " << endl;
				cin >> e1;
				sorter(set);
				rondas=check(tabla,set,disp,e1,rondas);

    }while(rondas>0);
    printSup(tabla,disp);
    cout << "Conseguiste " << tabla[16] << " puntos!!" << endl;
    cout << "¡Gracias por jugar!" << endl;

    return 0;
}
