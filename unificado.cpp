#include <mpi.h>
#include <iostream>

using namespace std;

int main (int argc, char *argv[]) {
   int num_processes = 0;
   int process_id = 0; 
   int name_length = 0;
   char host_name[MPI_MAX_PROCESSOR_NAME];
   int tag = 100;
   MPI_Status status; 

   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
   MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
   MPI_Get_processor_name(host_name, &name_length);
   
   if (process_id == 0) { // eres el receiver?
      int mensaje[5] = {-1, -1, -1, -1, -1};
      MPI_Recv(&mensaje, 5, MPI_INT, 1,tag, MPI_COMM_WORLD, &status);
      cout << "Soy el receiver " << process_id << " y recibi un mensaje" << endl;
      for (int i = 0; i < 5; i++){
        cout << "i = " << i << " valor = " << mensaje[i] << endl;
      } 
   } else { // entonces, eres el sender
      int mensaje[5] = {11, 12, 13, 14, 15};
      MPI_Send(&mensaje, 5, MPI_INT, 0, tag, MPI_COMM_WORLD);  
      cout << "Soy " << process_id << " y ya envie el arreglo" << endl; 
   }
   MPI_Finalize();

   return 0;
}