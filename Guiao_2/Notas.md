# Guiao 2 => Gestao de Processos

## Processo

> Um processo tem associado a si um espaço de endereçamento constituido por:
> - Codigo do Programa;
> - Heap;
> - Stack;

> Cada processo e identificado por um valor inteiro atribuido aquando da sua criaçao - **PID** *(Process Identifier)* 

## Hierarquia de processos

> Processo Pai, apresenta um valor de **PID** igual a x, cada filho que cria o **PID** de cada um sera **PID** + i, sendo o i o numero de filhos criados ate ao momento.
>
> Exemplo:
> 
> PID pai => 2034;
> 
> PID do Primeiro Filho => 2035;
> 
> PID do Segundo Filho => 2036;

## Criaçao de processos

> O processo-pai invoca a chamada ao sistema *fork()* para criar um processo-filho;
> 
> O processo-filho e um duplicado do processo-pai.
> - O processo-filho difere do processo-pai no seu **PID**;
> - Copia identica do espaço de endereçamento;
> - Registo de CPU;
> - Recursos abertos pelo processo-pai (ficheiros, etc);
> 
> Ambos os processos procedem a sua execuaçao concorrentemente.
> 
> Processos-filho podem criar outros processos, passando a ser pai desses mesmos.

> Chamada ao Sistema:
> - Descriçao: pid_t fork(void);
> - Cira um processo-filho a partir do processo atual;
> - Retorna, em caso de sucesso:
>   - O identificador de processo (**PID**) do processo-filho ao processo-pai;
>   - O valor 0 ao processo-filho;
> - Retorna -1 em caso de erro;

> Exemplo:
> 
> Processo-pai apresenta como recursos Ficheiro A e Recurso B.
> 
> Ao fazer fork() o processo filho e criado.
>
> Para devidir o codigo para o Processo pai do codigo do Processo filho, usar if.
>
> No if verificar se o **PID** e igual a 0 ou se e diferente.
> - Se for 0 entao o que esta dentro do if e codigo do processo filho;
> - Se for diferente entao o que esta no else e o codigo do processo pai;
>
> E de notar que os recursos do processo pai sao partilhados com os processos filhos.

## Terminaçao de processos

> O processo-filho termina a sua execuçao atraves da invocaçao da funçao *_exit*.
>
> O processo-pai pode aguardar que os processos-filho terminem atraves da chamada ao sistema *wait/waitpid*.
>
> O processo-pai pode aguardar por um procsso-filho em particular usando a chamada ao sistema *waitpid*.
>

> Chamada ao sistema:
> - Descriçao: pid_t wait(int *status);
> - Bloqueia a execuçao do processo ate um processo-filho terminar.
> - Retorno, em caso de sucesso:
>   - O identificador de processo (**PID**) do processo-filho que terminou.
>   - O valor do apontador *status* e atualizado com o codigo de terminaçao do processo-filho.
>
> O processo-pai pode verificar se o procesoo-filho terminou sem erros atraves da macro **WIFEXITED(status)**. O codigo de terminaçao e representado por apenas 8 bits e pode ser obtido com **WEXITSTATUS(status)**.
>

> Exemplo:
>
> Processo pai fica preso na chamada ao sistema **wait**, ate que o filho termine.
>
> Cado o processo filho atinge a chamada ao sistema **_exit(0)**, retorna o codigo passado por argumento.
>
> Quando a variavel **status** for atualizada com o codigo passado na chamada da funçao **_exit()** o processo pai continua a sua execuçao.

## Notas

> Se o processo-pai terminar antes do processo-filho, o processo-filho torna-se orfao.
> - Neste caso, o processo-filho e adotado pelo processo **initi**, cujo identificador de processo e 1.
>
> Um processo diz-se no estado *zombie* se este terminou e o seu processo-pai ainda n~ao o recolhe a correspondente informaçao usando o **wait**.
>
> As chamadas ao sistema **getpid** e **getppid** podem ser usadas para retornar o **PID** do processo atual e o **PID** do processo-pai, respetivamente.