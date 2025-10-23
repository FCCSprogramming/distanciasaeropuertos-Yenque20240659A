#include<iostream>
#include<random>
#include<iomanip>
using namespace std;

double** matrizDistanciaAeropuertos(int N);     //generar matriz de distancia de aeropuertos
void imprimirMatriz(double **arr, int N);       //mostrar la matriz de distancias de aeropuertos
double* promedioDistancias(double **arr, int N);    //generar un arreglo con el promedio de cada aeropuerto
int posMenorDistanciaPromedio(double *promd, int N);    //devolver la posicion fila de la menor distancia promedio
void liberarMatriz(double **&arr, int N);       //liberar memoria de la matriz de distancia
void liberarPromedio(double *&arr);     //liberar memoria del arreglo de promedios

int main(){

    int N;
    cout<<"\nIngrese el numero de aeropuertos: ";
    cin>>N;
    double **matriz=matrizDistanciaAeropuertos(N);

    if(matriz!=nullptr){        //ejecutamos si matriz no devuelve una matriz mayor o igual a 2x2
        //mostramos la matriz
        imprimirMatriz(matriz,N);

        //obtenemos un arreglo de promedios de cada aeropuerto
        double *promedio=promedioDistancias(matriz,N); //puntero apunta a un arreglo de promedios

        cout<<"El promedio de las distancias entre aeropuertos de cada aeropuerto: \n\n";
        //mostramos los promedios de cada aeropuerto
        for(int i=0; i<N; i++){
            cout<<"Aeropuerto["<<i+1<<"] : "<<promedio[i]<<" km\n";
        }
        cout<<"\n";

        //mostramos el aeropuerto con la menor distancia promedio hacia los demas
        int MDP=posMenorDistanciaPromedio(promedio,N);

        cout<<"El aeropuerto con menor distancia promedio hacia los demas: \n\n";
        cout<<"Aeropuerto["<<MDP+1<<"] : ";
        //mostramos la fila de distancias del aeropuerto con menor distancia promedio
        for(int j=0; j<N; j++){
            cout<<setw(9)<<matriz[MDP][j];
        }
        cout<<"\nPromedio: "<<promedio[MDP]<<" km\n\n";     //mostramos el promedio
        cout<<"\n\n";

        //liberamos la memoria de las matrices
        liberarMatriz(matriz,N);
        liberarPromedio(promedio);

        //verificamos que los punteros usados no esten colgados
        if(matriz==nullptr){
            cout<<"Puntero de matriz se modifico a nullptr\n";
        }
        if(promedio==nullptr){
            cout<<"Puntero de promedio se modifico a nullptr\n\n";
        }

    }else{
        cout<<"El numero de aeropuertos no puede ser menor que 2 para compararlas\n\n";
    }

    return 0;
}

double** matrizDistanciaAeropuertos(int N){
    //evitamos usar numeros menores a 2
    if(N>1){
        //reservar memoria para la matriz
        double **arr=new double*[N];

        for(int i=0; i<N; i++){
            arr[i]=new double[N];
        }

        //generar los elementos de la matriz
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(i!=j) arr[i][j]=i*j;    //asignamos numeros aleatorios
                else arr[i][j]=0;       //asignamos 0 la distancia de un aeropuerto
            }                           //con él mismo
        }

        //retornamos la direccion de la matriz
        return arr;
    }
    return nullptr;
}

void imprimirMatriz(double **arr, int N){
    cout<<"\n";
    //imprimimos la matriz
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout<<setw(9)<<arr[i][j];   //agregamos orden con setw()
        }
        cout<<"\n";
    }
    cout<<"\n";
}

double* promedioDistancias(double **arr, int N){
    //asignamos memoria a un arreglo tipo double
    double *promd=new double[N];

    for(int i=0; i<N; i++){
        double suma=0;
        for(int j=0; j<N; j++){
            suma+=arr[i][j];
        }
        promd[i]=(suma/(N-1));  //calculamos promedio de cada fila
    }
    //retormanos la direccion de un arreglo de promedios
    return promd;
}

int posMenorDistanciaPromedio(double *promd, int N){
    double minimo=promd[0];     //inicializamos el minimo
    int posMin=0;               //guarda la posicion fila del minimo

    for(int i=0; i<N; i++){
        if(promd[i]<minimo){
            minimo=promd[i];    //actualizamos valores
            posMin=i;
        }
    }
    //retornamos la posicion fila del aeropuerto con menor distancia promedio
    return posMin;
}

void liberarMatriz(double **&arr, int N){   //referencia a puntero para modificar el puntero en main()
    //liberamos memoria de la matriz
    for(int i=0; i<N; i++){
        delete[] arr[i];    //liberar memoria de cada fila
        arr[i]=nullptr;     //evitamos los punteros colgantes de fila
    }
    delete[] arr;   //liberamos memoria de **arr
    arr=nullptr;    //evitamos putero colgante
}

void liberarPromedio(double *&arr){     //referencia a puntero para modificar el puntero en main()
    delete[] arr;   //liberamos memoria del arreglo de promedios
    arr=nullptr;    //evitamos puntero colgante
}