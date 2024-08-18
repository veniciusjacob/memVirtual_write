# Memória Virtual em C - Processamento de Arquivos Grandes

## Descrição

Este projeto consiste em um programa em C que lê um arquivo de texto grande e o carrega na memória virtual utilizando o mapeamento de arquivos (`mmap`). O programa simula o processamento do arquivo em páginas de memória e permanece em execução para permitir o monitoramento do uso de memória.

## Objetivo

O objetivo deste programa é demonstrar o uso de memória virtual ao lidar com arquivos grandes e fornecer uma base para a análise de consumo de memória de processos em execução. É útil para estudos de sistemas operacionais, especialmente na parte de gerenciamento de memória.

## Funcionamento

1. **Mapeamento de Arquivo**: O arquivo de texto fornecido como entrada é mapeado para a memória virtual usando a função `mmap`. Este mapeamento permite que o arquivo seja tratado como se estivesse carregado diretamente na memória, mesmo que fisicamente ele não esteja completamente na RAM.

2. **Processamento em Páginas**: O programa simula o processamento do arquivo em partes (páginas) de tamanho fixo (definido por `PAGE_SIZE`). Cada página é acessada na memória para garantir que ela seja carregada.

3. **Execução Contínua**: Após o processamento inicial do arquivo, o programa entra em um loop infinito, esperando 10 segundos em cada iteração. Isso permite que o programa continue em execução para observação contínua do uso de memória.

## Estrutura do Código

### Funções Principais

- `load_file_into_memory(const char *filename)`: Esta função é responsável por mapear o arquivo na memória e processá-lo em páginas. Ela mantém o programa em execução após o processamento.

- `main(int argc, char *argv[])`: Função principal que inicia o programa e chama `load_file_into_memory` com o nome do arquivo passado como argumento.

### Definições Importantes

- `PAGE_SIZE`: Define o tamanho da página de memória que será usada para processar o arquivo.

## Como Utilizar

### Compilação

Para compilar o programa, use o seguinte comando:

```bash
gcc -o memvi mem_write_large.c
```