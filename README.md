# Mapeamento de Arquivo TXT para Memória Virtual

## Descrição

Este programa em C demonstra como mapear um arquivo TXT para a memória virtual utilizando a função `mmap`. O programa permite escrever conteúdo em um arquivo diretamente na memória mapeada, sincronizar essa memória com o arquivo no disco e exibir informações sobre o uso da memória virtual.

## Funcionalidades

- **Mapeamento de Arquivo:** Mapeia um arquivo TXT para a memória virtual.
- **Escrita na Memória Mapeada:** Escreve uma mensagem no arquivo diretamente na memória virtual.
- **Informações sobre Memória Virtual:** Exibe o endereço da memória mapeada e o tamanho do mapeamento.

## Requisitos

- GCC (GNU Compiler Collection) para compilar o programa.
- Um sistema operacional que suporte a função `mmap` (como Linux ou outros Unix-like).

## Compilação

Para compilar o programa, execute o seguinte comando no terminal:

```
gcc map_file_to_memory.c -o map_file_to_memory 
```

## Execução

Para executar o programa, use o seguinte comando, passando o nome do arquivo TXT que você deseja mapear para a memória:

```
./map_file_to_memory big-file.txt
```

## Saída Esperada

Após a execução, o programa exibirá informações sobre o mapeamento de memória:

```
Arquivo mapeado para a memória virtual e escrito com sucesso.
Endereço da memória mapeada: 0x7fcbf9d73000
Tamanho da memória mapeada: 4096 bytes
```

## Explicação dos Campos da Saída

- **Endereço da memória mapeada:** Este é o endereço na memória virtual onde o arquivo foi mapeado.

- **Tamanho da memória mapeada:** O tamanho total em bytes da memória virtual que foi alocada para o arquivo.

