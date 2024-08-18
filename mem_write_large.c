#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

// Tamanho da página de memória
#define PAGE_SIZE 4096

// Função para carregar o arquivo na memória virtual
void load_file_into_memory(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("Erro ao obter informações do arquivo");
        close(fd);
        exit(EXIT_FAILURE);
    }

    size_t file_size = st.st_size;
    size_t num_pages = (file_size + PAGE_SIZE - 1) / PAGE_SIZE; // Calcula o número de páginas necessárias

    // Mapeia o arquivo para a memória
    char *mapped_data = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (mapped_data == MAP_FAILED) {
        perror("Erro ao mapear arquivo na memória");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Escreve os dados do arquivo nas páginas de memória
    for (size_t i = 0; i < num_pages; i++) {
        printf("Processando página %zu/%zu\n", i + 1, num_pages);
        usleep(100000); // Simula processamento (100ms por página)

        // Acesso à memória mapeada para garantir que as páginas estejam carregadas na memória
        if (i * PAGE_SIZE < file_size) {
            mapped_data[i * PAGE_SIZE] = mapped_data[i * PAGE_SIZE];
        }
    }

    // Mantém o programa em execução para monitoramento
    while (1) {
        sleep(10); // Aguarda 10 segundos antes de repetir
    }

    // Desmapeia a memória e fecha o arquivo (não será alcançado neste exemplo)
    munmap(mapped_data, file_size);
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <arquivo_txt>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    load_file_into_memory(filename);

    return 0;
}
