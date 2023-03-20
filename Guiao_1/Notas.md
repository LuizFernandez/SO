# Guiao nº1

## Ficheiros

> Descritor de Ficheiro:
> - Representaçao abstrata de um ficheiro utilizada para operar sobre o mesmo;
> - Representado por um inteiro nao negativo;
> - Pode tambem servir para representar outros recursos de I/O;
>
> Descritores Standard:
>
> | Valor Inteiro | Nome            | \<unistd.h>   | \<stdio.h>|
> |---            |---              |---            |---        |
> | 0             | Standard input  | STDIN_FILENO  | stdin     |
> | 1             | Standard output | STDOUT_FILENO | stdout    |
> | 2             | Standard error  | STDERR_FILENO | stderr    |

## Estruturas Kernel

> Tabela de processo (TP)
> - Uma Tabela por processo;
> - Guarda descritores de ficheiros abertos;
> Nota: Com o comando **ulimit -n** sabe se quantos ficheiros pode se ter abertos.

> Tabela de Ficheiros (TF)
> - Tabela partilhada pelo sistema operativo;
> - Guarda o modo de abertura e a posiçao de leitura/escrita de cada descritor;

> V-node
> - Abstraçao de um objeto Kernel que respeita a interface de ficheiro **UNIX**;
> - Permite representar ficheiros, diretorias, FIFOs, *domain sockets*, ...
> - Guarda informaçao do tipo de objeto, apontadores para as funçoes sobre o mesmo e para o respetivo i-node;

> I-node
> - Guarda metadados/atributos do ficheiros (ex.: nome do ficheiro, tamanho, ...);
> - Guarda localizaçao dos dados no recurso f´isico de armazenamento;
>
> Nota: Em Linux, os i-nodes servem tambem como v-nodes, nao havendo uma implementaçao para os ultimos.

> Relaçoes entre as estruturas:
> - Entradas na tabela de ficheiros de sistema podem partilhar inodes, isto acontece quando o mesmo ficheiro a aberto em modos diferentes de abertura;
> - Descritores de processos disitintos podem partilhar entradas na tabela de ficheiros de sistema, com o uso de *fork*;
> - Descritores do mesmo processo podem partilhar entradas na tabela de ficheiros de sistema, via *dup*;

## Chamadas ao sistema

> Cabeçalhos/*headers*
> - \<unistd.h> - definiçoes e declaraçes de chamadas;
> - \<fcntl.h> - definiçao modos de abertura de ficheiro;
>   - O\_RDONLY, O\_WRONLY, O\_CREAT, O\_APPEND, O\_*;

Funçoes:

> Abertura de Ficheiros:
> - Definiçao: int open(const char* path, int oflag [, model]);
>   - inicializa um descritor para um determinado ficheiro;
>   - devolve o descritor ou erro;
>   - **path** - caminho do ficheiro;
>   - **oflag** - modo de abertura (O\_RDONLY, O\_WRONLY, ...);
>   - **mode** - permissoes de acesso para o O\_CREAT (usar 0640);


> Ler Ficheiro:
> - Definiçao: ssize\_t read(int fildes, void *buf, size\_t nbyte);
>   - devolve o numero de bytes lidos ou erro;
>   - **fildes** - descritor do ficheiro;
>   - **buf** - buffer para onde o conteudo e lido;
>   - **nbytes** - numero maximo de bytes a ler para o buffer;

> Escrita no Ficheiro: 
> - Definiçao: ssize\_t write(int fildes, const void* buf, size\_t nbytes);
>   - devolve o numero de bytes escritos ou erro;
>   - **fildes** - descritor do ficheiro;
>   - **buf** - buffer com conteudo a escrever;
>   - **nbyte** - numero de bytes a escrever;

> Fechar um Ficheiro:
> - Definiçao: int close(int fildes);
>   - apaga o descritor da tabeça do processo;
>   - devolve 0 caso a operaçao seja executada com sucesso, -1 caso contrario;
>   - **fildes** - descritor do ficheiro;

## Posiçao

> A cada operaçao de leitura/escrita efetuada sobre o mesmo descritor, a posiçao a ler/escrever e atualizada consoante o numero de bytes efetivamente lidos/escritos;
> Quando chega se ao final do ficheiro, ou seja, sem mais conteudo para ler, da se uma situaçao de EOF (*End of File*)

> Localizaçao do Apontador da posiçao
> - Descriçao: off\_t lseek(int fildes, off\_t offset, int whence)
>   - Relocalizar o apontador da posiçao, neste caso o descritor do ficheiro, numa dada posiçao;
>   - **whence**:
>       - SEEK\_SET => Inicio do ficheiro
>       - SEEK\_CUR => Posiçao Atual;
>       - SEEK\_END => Final do Ficheiro
>   - O movimento pode ser efetuado para a frente ou para tras, consuante o offset;


## Duvidas para o stor

> Na funçao de readln e nl, se o ficheiro terminar com um \n a funçao entra num ciclo infinito