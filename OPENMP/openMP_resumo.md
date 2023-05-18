# Resumão OpenMP

Autor: João Víctor Costa de Oliveira

## Conceitos e funções básicas, como usá-las e seus para que servem

1. **Diretivas de Compilação**: As diretivas de compilação são usadas para informar ao compilador como paralelizar o código. Elas são inseridas como pragmas diretamente no código-fonte. Alguns exemplos de diretivas do OpenMP são:

    * **#pragma omp parallel**: Cria uma região paralela, onde várias threads são criadas para executar o código em paralelo.

    * **#pragma omp for**: Paraleliza um loop for, distribuindo suas iterações entre as threads.

    * **#pragma omp sections**: Cria seções paralelas independentes, que podem ser executadas simultaneamente por diferentes threads.

    * **#pragma omp task**: Define uma tarefa que pode ser executada de forma assíncrona por qualquer thread disponível. As tarefas são executadas em paralelo, caso haja threads disponíveis.

    * **#pragma omp parallel sections**: Combina as diretivas parallel e sections, criando várias threads e seções paralelas dentro delas.

    * **#pragma omp master**: Especifica uma região de código que será executada apenas pela thread mestre, ou seja, a primeira thread a entrar na região paralela. É útil quando você tem uma seção de código que precisa ser executada apenas uma vez por toda a execução paralela.

    * **#pragma omp critical**: Especifica uma região crítica do código que só pode ser executada por uma thread de cada vez. Garante que apenas uma thread execute o código dentro da região crítica em um determinado momento, evitando condições de corrida.

    * **#pragma omp barrier**: Sincroniza todas as threads em um ponto específico do código. Garante que todas as threads tenham alcançado esse ponto antes de prosseguir. É útil quando você precisa garantir que todas as threads tenham concluído uma determinada parte do código antes de prosseguir.

    * **#pragma omp ordered**: Especifica uma região de código onde as iterações de um loop ou as seções paralelas devem ser executadas em uma ordem específica. É útil quando você precisa garantir que as iterações de um loop ou seções paralelas sejam executadas em uma ordem sequencial definida.

    * **#pragma omp taskwait**: Sincroniza a execução de tarefas criadas anteriormente usando a diretiva task. Garante que todas as tarefas tenham sido concluídas antes de prosseguir.

    * **#pragma omp taskloop**: Paraleliza um loop e cria tarefas para cada iteração. As iterações do loop são divididas entre as threads disponíveis, que criam tarefas para executar as iterações.

    * **#pragma omp target**: Especifica uma região de código que deve ser executada em um dispositivo de destino, como uma GPU. Essa diretiva é usada para offloading de tarefas em aceleradores.

    * **#pragma omp target teams**: Cria uma equipe de threads em um dispositivo de destino. Essa diretiva é usada em conjunto com #pragma omp distribute para distribuir iterações de um loop entre as equipes de threads.

    * **#pragma omp distribute**: Distribui iterações de um loop entre as equipes de threads geradas pela diretiva #pragma omp target teams. É usado em conjunto com #pragma omp target teams.

    * **#pragma omp simd**: Especifica que um loop pode ser executado de forma vetorializada, permitindo otimizações de vetorização por parte do compilador.

2. **Funções de Sincronização**: O OpenMP também fornece funções para sincronização de threads. Essas funções são usadas para controlar a execução paralela e garantir a coerência dos dados. Alguns exemplos de funções de sincronização são:

    * **omp_get_thread_num()**: Retorna o número da thread atual.

    * **omp_get_num_threads()**: Retorna o número total de threads em uma região paralela.

    * **omp_barrier()**: Sincroniza todas as threads em um ponto específico do código, garantindo que todas as threads tenham alcançado esse ponto antes de prosseguir.

    * **omp_set_num_threads()**: Define o número de threads a serem usadas em uma região paralela. Isso pode ser feito dinamicamente durante a execução do programa.

    * **omp_get_wtime()**: Retorna o tempo decorrido em segundos desde um ponto de referência fixo. Pode ser usado para medir o tempo de execução de uma determinada parte do código.

    * **omp_get_wtick()**: Retorna a menor unidade de tempo que pode ser medido usando omp_get_wtime(). É útil para obter a precisão da função omp_get_wtime().

    * **omp_get_max_threads()**: Retorna o número máximo de threads que podem ser utilizadas em uma região paralela.

    * **omp_get_num_procs()**: Retorna o número de processadores disponíveis no sistema.

    * **omp_get_nested()**: Retorna um valor indicando se o aninhamento de regiões paralelas está habilitado ou não.

    * **omp_get_dynamic()**: Retorna um valor indicando se o ajuste dinâmico de threads está habilitado ou não.

    * **omp_get_thread_limit()**: Retorna o número máximo de threads que podem ser criadas por uma região paralela.

    * **omp_get_cancellation()**: Retorna o estado da função de cancelamento de threads. Indica se as threads podem ser canceladas (TRUE) ou não (FALSE).

3. **Variáveis de Ambiente**: O OpenMP usa variáveis de ambiente para controlar o comportamento das regiões paralelas. Algumas variáveis de ambiente importantes são:

    * **OMP_NUM_THREADS**: Define o número máximo de threads a serem usadas em uma região paralela.

    * **OMP_SCHEDULE**: Especifica como as iterações de um loop devem ser atribuídas às threads.

    * **OMP_DYNAMIC**: Controla se o número de threads pode ser ajustado dinamicamente durante a execução.

    * **OMP_PROC_BIND**: Controla a vinculação de threads a núcleos de CPU físicos. Pode ser usado para melhorar o desempenho em sistemas com várias CPUs.

    * **OMP_SCHEDULE**: Especifica como as iterações de um loop devem ser atribuídas às threads. Pode ser configurado com diferentes políticas de escalonamento, como static, dynamic, guided, entre outras.

    * **OMP_NESTED**: Controla se o aninhamento de regiões paralelas é permitido (TRUE) ou não permitido (FALSE).

    * **OMP_DYNAMIC**: Controla se o ajuste dinâmico de threads é permitido (TRUE) ou não permitido (FALSE).

    * **OMP_PROC_BIND**: Controla a vinculação de threads a núcleos de CPU físicos. Pode ser configurado com opções como true, false ou master.

    * **OMP_STACKSIZE**: Especifica o tamanho da pilha em bytes para cada thread.

4. **Cláusulas**: Além das diretivas de compilação, o OpenMP também suporta cláusulas, que são usadas para especificar opções adicionais para controlar o comportamento das regiões paralelas. Algumas cláusulas comuns incluem:

    * **private**: Especifica variáveis locais para cada thread, garantindo que cada thread tenha sua própria cópia exclusiva da variável.

    * **shared**: Declara variáveis como compartilhadas entre todas as threads em uma região paralela.

    * **reduction**: Realiza uma operação de redução em uma variável compartilhada, como soma ou produto, atribuindo a cada thread uma cópia privada da variável e combinando os resultados no final.

    * **critical**: Especifica uma região crítica do código que só pode ser executada por uma thread de cada vez, evitando condições de corrida.

    * **atomic**: Garante a execução atômica de uma instrução, evitando condições de corrida em operações de leitura-modificação-escrita.

    * **Aninhamento de Regiões Paralelas**: O OpenMP permite o aninhamento de regiões paralelas, ou seja, a criação de uma nova região paralela dentro de uma região paralela existente. Isso pode ser útil quando você precisa paralelizar seções específicas de um código que já está sendo executado em paralelo.

    * **Escalabilidade**: O OpenMP oferece suporte a escalabilidade, permitindo que o número de threads seja ajustado dinamicamente durante a execução do programa. Isso pode ser feito usando a função omp_set_num_threads() para alterar o número de threads em uma região paralela ou a variável de ambiente OMP_DYNAMIC para controlar a alteração dinâmica de threads em todo o programa.

5. **Aninhamento de Regiões Paralelas**: O OpenMP permite o aninhamento de regiões paralelas, ou seja, a criação de uma nova região paralela dentro de uma região paralela existente. Isso pode ser útil quando você precisa paralelizar seções específicas de um código que já está sendo executado em paralelo.

6. **Escalabilidade**: O OpenMP oferece suporte a escalabilidade, permitindo que o número de threads seja ajustado dinamicamente durante a execução do programa. Isso pode ser feito usando a função omp_set_num_threads() para alterar o número de threads em uma região paralela ou a variável de ambiente OMP_DYNAMIC para controlar a alteração dinâmica de threads em todo o programa.

## Um passo a passo geral de como paralelizar um programa em Ansi-C com OpenMP

1. **Identifique seções paralelizáveis**: Analise seu código em busca de seções que podem ser executadas em paralelo. Isso geralmente envolve loops ou seções de código que podem ser executadas independentemente umas das outras.

2. **Inclua a biblioteca OpenMP**: No início do seu arquivo de código-fonte, adicione a diretiva de pré-processador

```
#include <omp.h> 
```

para incluir a biblioteca OpenMP.

3. **Defina uma região paralela**: Identifique a seção do código que você deseja paralelizar e coloque-a entre as diretivas

```
#pragma omp parallel 
```

e

```
#pragma omp end parallel

```

Isso cria uma região paralela onde várias threads podem executar em paralelo.

4. **Opcional**: Defina o número de threads: Se desejar controlar o número de threads a serem usadas, você pode usar a função

```
omp_set_num_threads() 
```

ou definir a variável de ambiente *OMP_NUM_THREADS* antes de executar o programa.

5. **Identifique variáveis compartilhadas e privadas**: Verifique quais variáveis são compartilhadas entre as threads e quais são privadas a cada thread. Variáveis compartilhadas podem ser acessadas por todas as threads, enquanto variáveis privadas têm uma cópia para cada thread.

6. **Anote as diretivas de compartilhamento de variáveis**: Use as diretivas apropriadas para definir o escopo e o comportamento das variáveis compartilhadas e privadas. Por exemplo, use private para declarar variáveis privadas e shared para declarar variáveis compartilhadas.

7. **Paralelize loops**: Para paralelizar loops, use a diretiva

```
#pragma omp for 
```

antes do loop. Isso divide as iterações do loop entre as threads disponíveis para execução em paralelo.

8. **Sincronize as threads, se necessário**: Se houver partes do código onde você precisa sincronizar as threads, use diretivas como

```
#pragma omp barrier
```

```
#pragma omp critical 
```

ou

```
#pragma omp atomic 
```

para garantir a exclusão mútua ou a sincronização adequada.

9. **Compile o programa com suporte ao OpenMP**: Certifique-se de compilar seu programa com suporte ao OpenMP. No caso do GCC, você pode usar a opção -fopenmp durante a compilação.

10. **Execute o programa**: Execute o programa paralelizado e verifique os resultados. Observe que os resultados podem variar de uma execução para outra devido à natureza não determinística da execução paralela.
