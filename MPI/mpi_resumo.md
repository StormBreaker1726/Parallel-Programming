# Resumão MPI
Autor: João Víctor Costa de Oliveira


## Funções básicas, como usá-las e seus para que servem

1. MPI_Init(int *argc, char ***argv): Esta função é usada para inicializar a biblioteca MPI em um programa paralelo. Os argumentos *argc e ***argv contêm o número de argumentos da linha de comando e os argumentos em si, respectivamente.

2. MPI_Comm_rank(MPI_Comm comm, int *rank): Esta função retorna o identificador do processo que está chamando. O primeiro argumento, MPI_Comm comm, é o comunicador que identifica o grupo de processos que podem se comunicar entre si. O segundo argumento, int *rank, é um ponteiro para a variável que receberá o identificador do processo.

3. MPI_Comm_size(MPI_Comm comm, int *size): Esta função retorna o número de processos no comunicador especificado. O primeiro argumento, MPI_Comm comm, é o comunicador que identifica o grupo de processos que podem se comunicar entre si. O segundo argumento, int *size, é um ponteiro para a variável que receberá o número de processos.

3. MPI_Send(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm): Esta função envia uma mensagem para outro processo. O primeiro argumento, void *buf, é um ponteiro para o buffer de dados a ser enviado. O segundo argumento, int count, é o número de elementos no buffer. O terceiro argumento, MPI_Datatype datatype, é o tipo de dado sendo enviado. O quarto argumento, int dest, é o identificador do processo de destino. O quinto argumento, int tag, é uma tag que pode ser usada para identificar a mensagem. O sexto argumento, MPI_Comm comm, é o comunicador que identifica o grupo de processos que podem se comunicar entre si.

4. MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status): Esta função recebe uma mensagem de outro processo. O primeiro argumento, void *buf, é um ponteiro para o buffer de dados onde a mensagem será armazenada. O segundo argumento, int count, é o número de elementos no buffer. O terceiro argumento, MPI_Datatype datatype, é o tipo de dado sendo recebido. O quarto argumento, int source, é o identificador do processo de origem. O quinto argumento, int tag, é uma tag que pode ser usada para identificar a mensagem. O sexto argumento, MPI_Comm comm, é o comunicador que identifica o grupo de processos que podem se comunicar entre si. O sétimo argumento, MPI_Status *status, é um ponteiro para uma estrutura que contém informações sobre a mensagem recebida.

5. MPI_Reduce(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm): Esta função realiza uma operação de redução em um grupo de processos e envia o resultado para um processo específico. O primeiro argumento, void *sendbuf, é um ponteiro para o buffer de dados a ser enviado. O segundo argumento, void *recvbuf, é um ponteiro para o buffer de dados onde o resultado será armazenado. O terceiro argumento, int count, é o número de elementos nos buffers. O quarto argumento, MPI_Datatype datatype, é o tipo de dado sendo reduzido. O quinto argumento, MPI_Op op, é a operação de redução a ser realizada. O sexto argumento, int root, é o identificador do processo que receberá o resultado. O sétimo argumento, MPI_Comm comm, é o comunicador que identifica o grupo de processos que serão reduzidos.

6. MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm): Esta função envia uma mensagem de broadcast de um processo para todos os outros processos no comunicador. O primeiro argumento, void *buffer, é um ponteiro para o buffer de dados a ser enviado. O segundo argumento, int count, é o número de elementos no buffer. O terceiro argumento, MPI_Datatype datatype, é o tipo de dado sendo enviado. O quarto argumento, int root, é o identificador do processo que está transmitindo a mensagem. O quinto argumento, MPI_Comm comm, é o comunicador que identifica o grupo de processos que podem se comunicar entre si.

7. MPI_Barrier(MPI_Comm comm): Esta função espera até que todos os processos no comunicador atinjam o mesmo ponto antes de continuar a execução. O argumento, MPI_Comm comm, é o comunicador que identifica o grupo de processos que precisam esperar.

8. MPI_Scatter(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm): A função MPI_Scatter envia dados de um processo (o processo raiz) para todos os outros processos no comunicador. Os dados são divididos em partes iguais e enviados para cada processo. O primeiro argumento, void *sendbuf, é o buffer de envio do processo raiz, que contém os dados a serem enviados. O segundo argumento, int sendcount, é o número de elementos enviados para cada processo. O terceiro argumento, MPI_Datatype sendtype, é o tipo de dado sendo enviado. O quarto argumento, void *recvbuf, é o buffer de recepção para o processo que recebe os dados. O quinto argumento, int recvcount, é o número de elementos recebidos de cada processo. O sexto argumento, MPI_Datatype recvtype, é o tipo de dado sendo recebido. O sétimo argumento, int root, é o identificador do processo raiz que está enviando os dados. O último argumento, MPI_Comm comm, é o comunicador que identifica o grupo de processos que podem se comunicar entre si.

9. MPI_Gather(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm): A função MPI_Gather recebe dados de todos os processos no comunicador e os coleta em um único processo (o processo raiz). O primeiro argumento, void *sendbuf, é o buffer de envio para cada processo, que contém os dados a serem enviados. O segundo argumento, int sendcount, é o número de elementos enviados de cada processo. O terceiro argumento, MPI_Datatype sendtype, é o tipo de dado sendo enviado. O quarto argumento, void *recvbuf, é o buffer de recepção do processo raiz, que recebe os dados de todos os outros processos. O quinto argumento, int recvcount, é o número total de elementos recebidos. O sexto argumento, MPI_Datatype recvtype, é o tipo de dado sendo recebido. O sétimo argumento, int root, é o identificador do processo raiz que está coletando os dados. O último argumento, MPI_Comm comm, é o comunicador que identifica o grupo de processos que podem se comunicar entre si.

10. MPI_AllGather(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm): A função MPI_AllGather é semelhante a MPI_Gather, exceto que ela coleta dados de todos os processos no comunicador e os distribui para todos os outros processos. Cada processo recebe os dados de todos os outros processos, incluindo seu próprio. O primeiro argumento, void *sendbuf, é o buffer de envio para cada processo, que contém os dados a serem enviados. O segundo argumento, int sendcount, é o número de elementos enviados de cada processo. O terceiro argumento, MPI_Datatype sendtype, é o tipo de dado sendo enviado. O quarto argumento, void *recvbuf, é o buffer de recepção para cada processo, que recebe os dados de todos os outros processos. O quinto argumento, int recvcount, é o número total de elementos recebidos de cada processo. O sexto argumento, MPI_Datatype recvtype, é o tipo de dado sendo recebido. O último argumento, MPI_Comm comm, é o comunicador que identifica o grupo de processos que podem se comunicar entre si.



## Um passo a passo geral de como paralelizar um programa em Ansi-C com MPI

1. Incluir as bibliotecas MPI no início do código:

```
#include <mpi.h>
```

2. Inicializar o ambiente MPI no início do programa:

```
MPI_Init(&argc, &argv);
```

3. Obter o número total de processos e o identificador de cada processo no comunicador padrão:

```
int world_rank, world_size;
MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
MPI_Comm_size(MPI_COMM_WORLD, &world_size);
```

4. Dividir o trabalho em partes iguais para cada processo:

```
int my_start = (total_elements / world_size) * world_rank;
int my_end = (total_elements / world_size) * (world_rank + 1) - 1;
```

5. Distribuir os dados entre os processos:

```
MPI_Scatter(data, chunk_size, MPI_INT, my_data, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
```

6. Processar os dados em paralelo:

```
for (int i = 0; i < chunk_size; i++) 
{
    my_data[i] = my_data[i] * 2;
}
```

7. Juntar os resultados de volta em um único processo:

```
MPI_Gather(my_data, chunk_size, MPI_INT, data, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
```

8. Finalizar o ambiente MPI ao final do programa:

```
MPI_Finalize();
```

Obviamente, o processo de paralelização de um código é altamente dependente do problema em questão e dos recursos de hardware disponíveis. Portanto, este é apenas um exemplo geral que pode ser adaptado para diferentes situações. É importante lembrar também que a comunicação entre processos em MPI pode ser custosa em termos de desempenho, por isso é importante minimizar a quantidade de comunicação necessária e maximizar o tempo de processamento paralelo.

Além disso, alguns outros passos importantes para paralelizar um código em ANSI-C com MPI incluem:

1. Definir corretamente o tipo de dado sendo enviado/recebido, usando o MPI_Datatype apropriado.

2. Verificar se há dependências entre as operações que estão sendo realizadas e considerar se alguma sincronização é necessária.

3. Otimizar a carga de trabalho em cada processo para garantir que todos os processadores estejam ocupados durante a execução do programa.

4. Verificar se há limitações de recursos (como memória, por exemplo) que possam afetar o desempenho da execução paralela.

5. Testar o código em diferentes configurações de hardware e ajustar os parâmetros de acordo com os resultados obtidos.

6. Usar ferramentas de profiling e depuração para identificar possíveis gargalos de desempenho e otimizar o código.