#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define PAGE_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("Error getting file size");
        close(fd);
        return EXIT_FAILURE;
    }
    size_t file_size = st.st_size;

    size_t offset = 0;
    while (offset < file_size) {
        size_t bytes_to_map = (file_size - offset) < PAGE_SIZE ? (file_size - offset) : PAGE_SIZE;

        void *mapped_memory = mmap(NULL, bytes_to_map, PROT_READ, MAP_PRIVATE, fd, offset);
        if (mapped_memory == MAP_FAILED) {
            perror("Error mapping memory");
            close(fd);
            return EXIT_FAILURE;
        }

        printf("Mapped %zu bytes at offset %zu to memory\n", bytes_to_map, offset);

        if (munmap(mapped_memory, bytes_to_map) == -1) {
            perror("Error unmapping memory");
            close(fd);
            return EXIT_FAILURE;
        }

        offset += bytes_to_map;
    }

    close(fd);

    return EXIT_SUCCESS;
}
