// Implementación computacional del taller 7 de estadística bayesiana en C++

#include "math.h"
#include "random"
#include "iostream"
#include "vector"
#include "iomanip"
#include "fstream"
#include "string"
#include "ctime"
#include "algorithm"

using namespace std;

vector<double> readSchool(int num);

void printVec(vector<double> vec);

void printVec(double * A,int len);

double vecSum(vector<double> vec);

double vecSum(double * A, int len);

int vecSum(bool * A, int len);

double rThetaj(double mu, double tau2, int nj, double yBarj, double sig2);

double rSigma2(double nu_0, int n, double sigma2_0, double SUM);

double rMu(double mu_0,double gamma2_0, int m, double theMean, double tau2);

double rTau2(double eta_0, int m, double tau2_0, double SS);

int main(){
    //
    srand(time(NULL));

    // Leer archivos
    vector<vector<double>> schools;
    for(int k=1;k<9;k++)
        schools.push_back(readSchool(k));

    // Establecer hiperparámetros:
    double mu_0 = 7,gamma2_0 = 5, tau2_0 = 10, eta_0 = 2, sigma2_0 = 15, nu_0 = 2;
    int m = 8;

    // Establecer parámetros de la simulación
    cout << "Inserte la cantidad de iteraciones del periodo de calentamiento: ";
    int bp; cin >> bp;
    cout << "Inserte la cantidad de iteraciones del algoritmo: ";
    int B; cin >> B;

    // Cálculo de estadísticas necesarias
    vector<double> schMeans; // Medias
    for(vector<double> v: schools)
        schMeans.push_back(vecSum(v)/v.size());
    vector<int> sSize; // n_j
    for(vector<double> v: schools)
        sSize.push_back(v.size());
    int n = 0; // n
    for(int nj: sSize)
        n += nj;

    // Almacenamiento de resultados
    double ** Thetas;
    Thetas = new double *[m];
    for(int j=0;j<m;j++)
        *(Thetas+j) = new double [B];
    double * Mu, * Sigma2, * Tau2;
    Sigma2 = new double [B];
    Mu = new double [B];
    Tau2 = new double [B];

    // Asignación de valores iniciales
    for(int j=0;j<m;j++)
        Thetas[j][0] = 10; // Valor que estimo según mi experiencia personal en el colegio
    Sigma2[0] = 100; // Previa difusa que refleja mi gran incertidumbre
    Mu[0] = 10;
    Tau2[0] = 100; // Hago Tau=Sigma2 pues no sé si hay más variablilidad dentro o entre los colegios

    // Periodo de calentamiento
    cout << "Iniciando periodo de calentamiento de " << bp << " iteraciones." << endl;
    double SUM,theMean,SS;
    for(int i=0;i<bp;i++){

        // Thetas
        for(int j=0;j<m;j++)
            Thetas[j][0] = rThetaj(Mu[0],Tau2[0],sSize[j],schMeans[j],Sigma2[0]);

        // Sigma^2
        SUM = 0;
        for(int j=0;j<m;j++)
            for(double v: schools[j])
                SUM += pow(v-Thetas[j][0],2);
        Sigma2[0] = rSigma2(nu_0,n,sigma2_0,SUM);

        // Mu
        theMean = 0;
        for (int j=0;j<m;j++)
            theMean += Thetas[j][0];
        theMean /= m;
        Mu[0] = rMu(mu_0,gamma2_0,m,theMean,Tau2[0]);

        // Tau^2
        SS = 0;
        for(int j=0;j<m;j++)
            SS += pow(Thetas[j][0]-Mu[0],2);
        Tau2[0] = rTau2(eta_0,m,tau2_0,SS);
    }

    // Ejecusión del algoritmo
    cout << "Iniciando el muestreador con " << B << " teraciones." << endl;
    for(int i=1;i<B;i++){

        // Thetas
        for(int j=0;j<m;j++)
            Thetas[j][i] = rThetaj(Mu[i-1],Tau2[i-1],sSize[j],schMeans[j],Sigma2[i-1]);

        // Sigma^2
        SUM = 0;
        for(int j=0;j<m;j++)
            for(double v: schools[j])
                SUM += pow(v-Thetas[j][i],2);
        Sigma2[i] = rSigma2(nu_0,n,sigma2_0,SUM);

        // Mu
        theMean = 0;
        for (int j=0;j<m;j++)
            theMean += Thetas[j][i];
        theMean /= m;
        Mu[i] = rMu(mu_0,gamma2_0,m,theMean,Tau2[i-1]);

        // Tau^2
        SS = 0;
        for(int j=0;j<m;j++)
            SS += pow(Thetas[j][i]-Mu[i],2);
        Tau2[i] = rTau2(eta_0,m,tau2_0,SS);
    }
    cout << "Simulación completada satisfactoriamente." << endl;

		// Creación de archivo de resultados.

		string resName = "results.md";
		ofstream out(resName);

		out << "# Análisis Bayesiano de las horas de estudio de los estudiantes de ocho colegios" << endl;
		out << "## Modelo bayesiano normal jerarquico con varianza común a los colegios" << endl;
		out << "##### Samuel Sánchez" << endl;
		time_t now = time(0);
		char * dt = ctime(&now);
		out << "##### " << dt << endl;

		out << "## Muestreador" << endl;
		out << "Se ejecutó el algoritmo con " << bp << " iteraciones del periodo de calentamiento, " << B << " iteraciones reales y los siguientes valores iniciales:" << endl << endl;
		out << " * $\\theta_j=0$ para $j=1,2,...,8.$" << endl;
		out << " * $\\sigma^2=100$" << endl;
		out << " * $\\mu^2=0$" << endl;
		out << " * $\\tau^2=100$" << endl << endl;


    // Evaluación de la convergencia
		out << "## Evaluación de la convergencia" << endl;


    // Medias posteriores e intervalos de confianza
		out << "## Medias posteriores e intervalos de confianza al 95%" << endl;

		// Ordenar vectores
		sort(Sigma2, Sigma2+B,[](int x, int y){ return x < y; });
		sort(Mu, Mu+B,[](int x, int y){ return x < y; });
		sort(Tau2, Tau2+B,[](int x, int y){ return x < y; });

		int lIndex = round(B*0.05),uIndex = round(B*0.95);

		out << "|Parámetro|q0.05|Media|q0.95|" << endl;
		out << "|:-------:|----:|----:|----:|" << endl;
		out << "|$\\sigma^2$|" << *(Sigma2 + lIndex - 1) << "|" << vecSum(Sigma2,B)/B << "|" << *(Sigma2 + uIndex - 1) << "|" << endl;
		out << "|$\\mu$|" << *(Mu + lIndex - 1) << "|" << vecSum(Mu,B)/B << "|" << *(Mu + uIndex - 1) << "|" << endl;
		out << "|$\\tau^2$|" << *(Tau2 + lIndex - 1) << "|" << vecSum(Tau2,B)/B << "|" << *(Tau2 + uIndex - 1) << "|" << endl << endl;


		// Densidad posterior de R
		out << "## Estudio de R" << endl;
		out << "$R=\\tau^2/(\\tau^2+\\sigma^2)$" << endl << endl;

		double * R;
		R = new double [B];
		transform(Sigma2,Sigma2+B,Tau2,R,
						[](double s,double t){return t/(s+t);});

		sort(R, R+B,[](int x, int y){ return x < y; });

    double minR = *R, maxR = *(R+B-1),dr = (maxR - minR)/20.0;

		vector<double> densityR(20);

		for(int l=0;l<B;l++)
				densityR[floor((*(R+l)-minR)/dr)]++;

		out << "### Densidad de R:" << endl;
		for(int l=0;l<20;l++){
				out << minR+l*dr << " - " << minR+(l+1)*dr << " :";
				out << string(densityR[l]/B*200,'-') << endl << endl;
		}
		out << endl << endl;

        // printVec(densityR);

    // P(the7<the6) y P(the7=min{the1,...,the8})
		out << "## Algunas probabilidades" << endl;

        bool * P1;
        P1 = new bool [B];
        transform(Thetas[7],Thetas[7]+B,Thetas[6],P1,
            [](double x,double y){return x<y;});
        double p1 = (double)vecSum(P1,B) / (double)B;

        out << "$P(\\theta_7<\\theta_6)=$" << p1 << endl << endl;

        bool * P2;
        P2 = new bool [B];
        for(int l=0;l<B;l++)
            *(P2+l) = (Thetas[7][l]<Thetas[1][l])*(Thetas[7][l]<Thetas[2][l])*(Thetas[7][l]<Thetas[3][l])*(Thetas[7][l]<Thetas[4][l])*(Thetas[7][l]<Thetas[5][l])*(Thetas[7][l]<Thetas[6][l])*(Thetas[7][l]<Thetas[8][l]);
        double p2 = (double)vecSum(P2,B) / (double)B;

        out << "$P(\\theta_7=min\\{\\theta_1,\\theta_2,...,\\theta_8\\})=$" << p2 << endl << endl;

    // Medias muestrales vs medias posteriores
		vector<double> posMeans;
		double tmp1;
		for(int j=0;j<m;j++){
				tmp1 = 0.0;
				for(int i=0;i<B;i++)
						tmp1 += Thetas[j][i];
				posMeans.push_back(tmp1/B);
		}

		out << "## Comparación de medias muestrales y medias posteriores" << endl;
		out << "|Colegio|No Estudiantes|Media Muestral|Media Posterior|" << endl;
		out << "|:-----:|:------------:|-------------:|--------------:|" << endl;
		for(int j=0;j<m;j++)
				out << "|" << j+1 << "|" << sSize[j] << "|" << schMeans[j] << "|" << posMeans[j] << "|" << endl;


		out.close();

        /*
		cout << "Generando informe en html" << endl;
		cout << "-> Recuerde que para que este paso se complete satisfactoriamente se requiere que pandoc esté instalada en el equipo y haga parte del path" << endl;
		system("pandoc results.md -o results.html");
        */

    return 0;
}

vector<double> readSchool(int num){ //Leer archivo CSV de una sola columna
    vector<double> school;

    string name = "school"+to_string(num)+".csv";
    ifstream data(name); // Abrir archivo
    double x;

    while(data >> x){
        school.push_back(x);
    }

    data.close(); // Cerrar archivo

    return school;
}

void printVec(vector<double> vec){ // Imprimir vector en pantalla
    for(double v: vec)
        cout << v << " ";
    cout << endl;
}

void printVec(double * A,int len){
		for(int l=0;l<len;l++)
				cout << *(A+l) << " ";
		cout << endl;
}

double vecSum(vector<double> vec){
    double sum = 0;
    for(double v: vec)
        sum += v;
    return sum;
}

double vecSum(double * A, int len){
		double sum = 0;
		for(int l=0;l<len;l++)
				sum += *(A+l);
		return sum;
}

int vecSum(bool * A, int len){
    int sum = 0;
    for(int l=0;l<len;l++)
        sum += *(A+l);
    return sum;
}

double rThetaj(double mu, double tau2, int nj, double yBarj, double sig2){
    double V = 1.0/(1.0/tau2+nj/sig2);
    double vE = (mu/tau2+nj*yBarj/sig2)*V;
    //
    default_random_engine e;
    normal_distribution<double> dN(vE,V);
    //
    return dN(e);
}

double rSigma2(double nu_0, int n, double sigma2_0, double SUM){
    double A = (nu_0+n)/2;
    double _B = 2/(nu_0*sigma2_0+SUM);
    //
    default_random_engine e;
    gamma_distribution<double> dG(A,_B);
    //
    return 1.0/dG(e);
}

double rMu(double mu_0,double gamma2_0, int m, double theMean, double tau2){
    double V = 1.0/(1.0/gamma2_0+m/tau2);
    double vE = (mu_0/gamma2_0+m*theMean/tau2)*V;
    //
    default_random_engine e;
    normal_distribution<double> dN(vE,V);
    //
    return dN(e);
}

double rTau2(double eta_0, int m, double tau2_0, double SS){
    double A = (eta_0+m)/2;
    double _B = 2/(eta_0*tau2_0+SS);
    //
    default_random_engine e;
    gamma_distribution<double> dG(A,_B);
    //
    return 1.0/dG(e);
}
