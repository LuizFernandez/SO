# Guiao nº3 => Execs

## Exec
> A familia de funçoes *exec* substitui o programa em execuçao num certo processo pelo novo programa especificado como argumento.
>
> Instruçoes e dadots sao substituidos.
>
> *Pid*, descritores e estruturas em *Kernel* sao mantidos.

## Utilidade

> *Fork* + *Exec* - **interpretador de comandos** - processo pai cria um filho via o comando *fork()* e o filho executa um novo program via o comando *exec()*.

## Chamadas ao sistema

> Bibliotecas: <unistd.h> - definiçoes e declaraçoes de chamadas
>
> Definiçao: int execl(const char *path, const char* arg0, ..., NULL);
> - troca o programa em execuçao pelo executavel definido pelos argumentos da funçao;
> - **path** - caminho completo para o executavel;
> - **arg0** - nome do executavel;
> - **arg1,...,NULL** - argumentos do execitavel. O ultimo argumento tem de ter o valor NULL;
> - apenas retorna o valor em caso de erro
>   - Devido a isto e que tem que se usar **fork** antes de usar o **exec** pois o programa principal ou pai, apos executar **exec** com sucesso termina, deixando por fazer o resto do programa.
>
> Definiçao: int execlp(const char *file, const char *arg0, ..., NULL);
> - Semelhante a chamada anterior mas recorre aos caminhos registados na variavel de ambiente **PATH**;
> - Exemplo: em vez de "/bin/ls" o argumento file poderia ser apenass "ls";
>
> Definiçoes: 
> - int execv(const char *path, char *const argv[]);
> - int execvp(const char *path, char *const argv[]);
>   - Semelhantes as chamadas anterior mas recebe argumentos do executavel como um array (**argv**);
>   - Primeira posiçao do array **argv** deve conter o nome do executavel. A ultima deve conter o valor **NULL**;