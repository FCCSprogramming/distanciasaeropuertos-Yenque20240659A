#include<iostream>
#include<random>
#include<iomanip>
using namespace std;

double** matrizDistanciaAeropuertos(int N);
void imprimirMatriz(double **arr, int N);
double* promedioDistancias(double **arr, int N);
int posMenorDistanciaPromedio(double *promd, int N);

int main(){

    int N;
    cout<<"\nIngrese el numero de aeropuertos: ";
    cin>>N;
    double **matriz=matrizDistanciaAeropuertos(N);

    if(matriz!=nullptr){
        //mostramos la matriz
        imprimirMatriz(matriz,N);

        //obtenemos un arreglo de promedios de cada aeropuerto
        double *promedio=promedioDistancias(matriz,N);
        cout<<"El promedio de las distancias entre aeropuertos de cada aeropuerto: \n\n";
        for(int i=0; i<N; i++){
            cout<<"Aeropuerto["<<i+1<<"] : "<<promedio[i]<<" km\n";
        }
        cout<<"\n";

        //mostramos el aeropuerto con la menor distancia promedio hacia los demas
        int MDP=posMenorDistanciaPromedio(promedio,N);
        cout<<"El aeropuerto con menor distancia promedio hacia los demas: \n\n";
        cout<<"Aeropuerto["<<MDP+1<<"] : ";
        for(int j=0; j<N; j++){
            cout<<setw(9)<<matriz[MDP][j];
        }
        cout<<"\nPromedio: "<<promedio[MDP]<<" km\n\n";
        cout<<"\n\n";
    }else{
        cout<<"El numero de aeropuertos no puede ser menor que 2 para compararlas\n\n";
    }

    return 0;
}

double** matrizDistanciaAeropuertos(int N){
    //evitamos usar numeros igual o menor que 0
    if(N>1){
        //reservar memoria para la matriz
        double **arr=new double*[N];
        for(int i=0; i<N; i++){
            arr[i]=new double[N];
        }
        //generar los elementos de la matriz
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(i!=j) arr[i][j]=1;
                else arr[i][j]=0;
            }
        }
        //retornamos la direccion de la matriz
        return arr;
    }
    return nullptr;
}

void imprimirMatriz(double **arr, int N){
    cout<<"\n";
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout<<setw(9)<<arr[i][j];
        }
        cout<<"\n";
    }
    cout<<"\n";
}

double* promedioDistancias(double **arr, int N){
    double *promd=new double[N];
    for(int i=0; i<N; i++){
        double suma=0;
        for(int j=0; j<N; j++){
            suma+=arr[i][j];
        }
        promd[i]=(suma/(N-1));
    }
    return promd;
}

int posMenorDistanciaPromedio(double *promd, int N){
    double minimo=promd[0];
    int posMin=0;
    for(int i=0; i<N; i++){
        if(promd[i]<minimo){
            minimo=promd[i];
            posMin=i;
        }
    }
    return posMin;
}