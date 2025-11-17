#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 10000
#define MAX_STOPWORDS 500
#define MAX_WORD_LEN 100
#define MAX_LINE_LEN 2000

// Node cho danh sách liên kết các số dòng
typedef struct LineNode {
    int line_number;
    struct LineNode *next;
} LineNode;

// Cấu trúc lưu trữ từ và các dòng xuất hiện
typedef struct {
    char word[MAX_WORD_LEN];
    LineNode *lines_head;
    int line_count;
} IndexEntry;

// Mảng chứa các từ stop
char stopwords[MAX_STOPWORDS][MAX_WORD_LEN];
int stopword_count = 0;

// Mảng chứa bảng chỉ dẫn
IndexEntry index_table[MAX_WORDS];
int index_count = 0;

// Tạo file stopwords mặc định
void create_default_stopwords(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Khong the tao file stopwords: %s\n", filename);
        return;
    }
    
    const char *default_stopwords[] = {
        "a", "an", "and", "are", "as", "at", "be", "but", "by",
        "for", "if", "in", "into", "is", "it", "no", "not", "of",
        "on", "or", "such", "that", "the", "their", "then", "there",
        "these", "they", "this", "to", "was", "will", "with", "had",
        "have", "has", "would", "could", "should", "been", "being",
        "were", "what", "which", "who", "whom", "whose", "where",
        "when", "why", "how", "all", "any", "both", "each", "few",
        "more", "most", "other", "some", "can", "may", "must", "shall",
        NULL
    };
    
    for (int i = 0; default_stopwords[i] != NULL; i++) {
        fprintf(file, "%s\n", default_stopwords[i]);
    }
    
    fclose(file);
    printf("Da tao file stopwords mac dinh: %s\n", filename);
}

// Đọc danh sách stopwords từ file
void load_stopwords(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File stopwords khong ton tai. Dang tao file mac dinh...\n");
        create_default_stopwords(filename);
        file = fopen(filename, "r");
        if (file == NULL) {
            printf("Khong the tao/mo file stopwords: %s\n", filename);
            return;
        }
    }
    
    char word[MAX_WORD_LEN];
    while (fgets(word, MAX_WORD_LEN, file) != NULL && stopword_count < MAX_STOPWORDS) {
        word[strcspn(word, "\n")] = 0;
        for (int i = 0; word[i]; i++) {
            word[i] = tolower(word[i]);
        }
        if (strlen(word) > 0) {
            strcpy(stopwords[stopword_count++], word);
        }
    }
    
    fclose(file);
    printf("Da doc %d stopwords\n", stopword_count);
}

// Kiểm tra xem từ có phải là stopword không
int is_stopword(const char *word) {
    for (int i = 0; i < stopword_count; i++) {
        if (strcmp(word, stopwords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Kiểm tra xem ký tự trước đó có phải là dấu chấm không
int is_after_period(const char *line, int pos) {
    for (int i = pos - 1; i >= 0; i--) {
        if (line[i] == '.') {
            return 1;
        }
        if (!isspace(line[i])) {
            return 0;
        }
    }
    return 0;
}

// Tìm vị trí của từ trong bảng chỉ dẫn
int find_word(const char *word) {
    for (int i = 0; i < index_count; i++) {
        if (strcmp(index_table[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

// Thêm số dòng vào danh sách của từ
void add_line_number(int index, int line_num) {
    // Kiểm tra xem số dòng đã tồn tại chưa
    LineNode *current = index_table[index].lines_head;
    while (current != NULL) {
        if (current->line_number == line_num) {
            return; // Đã tồn tại
        }
        current = current->next;
    }
    
    // Thêm số dòng mới
    LineNode *new_node = (LineNode*)malloc(sizeof(LineNode));
    if (new_node == NULL) {
        printf("Loi cap phat bo nho!\n");
        return;
    }
    
    new_node->line_number = line_num;
    new_node->next = index_table[index].lines_head;
    index_table[index].lines_head = new_node;
    index_table[index].line_count++;
}

// So sánh hai IndexEntry để sắp xếp
int compare_entries(const void *a, const void *b) {
    return strcmp(((IndexEntry*)a)->word, ((IndexEntry*)b)->word);
}

// Xử lý một từ
void process_word(const char *original_word, int line_num, const char *line, int word_pos) {
    // Bỏ qua từ quá ngắn
    if (strlen(original_word) < 2) {
        return;
    }
    
    // Kiểm tra từ riêng (bắt đầu bằng chữ hoa và không sau dấu chấm)
    if (isupper(original_word[0]) && !is_after_period(line, word_pos)) {
        return;
    }
    
    // Chuyển thành chữ thường
    char word[MAX_WORD_LEN];
    int i;
    for (i = 0; i < strlen(original_word) && i < MAX_WORD_LEN - 1; i++) {
        word[i] = tolower(original_word[i]);
    }
    word[i] = '\0';
    
    // Kiểm tra stopword
    if (is_stopword(word)) {
        return;
    }
    
    // Tìm từ trong bảng chỉ dẫn
    int idx = find_word(word);
    if (idx == -1) {
        // Thêm từ mới
        if (index_count < MAX_WORDS) {
            strcpy(index_table[index_count].word, word);
            index_table[index_count].lines_head = NULL;
            index_table[index_count].line_count = 0;
            add_line_number(index_count, line_num);
            index_count++;
        } else {
            static int warning_shown = 0;
            if (!warning_shown) {
                printf("Canh bao: Da dat gioi han so tu (%d). Mot so tu se bi bo qua.\n", MAX_WORDS);
                warning_shown = 1;
            }
        }
    } else {
        // Cập nhật từ đã có
        add_line_number(idx, line_num);
    }
}

// Xử lý văn bản
void process_text(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Khong the mo file van ban: %s\n", filename);
        return;
    }
    
    char *line = (char*)malloc(MAX_LINE_LEN);
    if (line == NULL) {
        printf("Loi cap phat bo nho!\n");
        fclose(file);
        return;
    }
    
    int line_num = 0;
    
    while (fgets(line, MAX_LINE_LEN, file) != NULL) {
        line_num++;
        
        if (line_num % 100 == 0) {
            printf("Dang xu ly dong %d...\r", line_num);
            fflush(stdout);
        }
        
        int i = 0;
        while (line[i]) {
            while (line[i] && !isalpha(line[i])) {
                i++;
            }
            
            if (!line[i]) break;
            
            int word_start = i;
            char word[MAX_WORD_LEN];
            int j = 0;
            while (line[i] && isalpha(line[i]) && j < MAX_WORD_LEN - 1) {
                word[j++] = line[i++];
            }
            word[j] = '\0';
            
            if (j > 0) {
                process_word(word, line_num, line, word_start);
            }
        }
    }
    
    free(line);
    fclose(file);
    printf("\nDa xu ly %d dong\n", line_num);
}

// Sắp xếp các số dòng trong một entry
void sort_line_numbers(int index) {
    if (index_table[index].line_count <= 1) return;
    
    // Chuyển danh sách liên kết thành mảng
    int *lines = (int*)malloc(index_table[index].line_count * sizeof(int));
    if (lines == NULL) return;
    
    LineNode *current = index_table[index].lines_head;
    int i = 0;
    while (current != NULL) {
        lines[i++] = current->line_number;
        current = current->next;
    }
    
    // Sắp xếp mảng (bubble sort đơn giản)
    for (i = 0; i < index_table[index].line_count - 1; i++) {
        for (int j = 0; j < index_table[index].line_count - i - 1; j++) {
            if (lines[j] > lines[j + 1]) {
                int temp = lines[j];
                lines[j] = lines[j + 1];
                lines[j + 1] = temp;
            }
        }
    }
    
    // Xây dựng lại danh sách liên kết
    while (index_table[index].lines_head != NULL) {
        LineNode *temp = index_table[index].lines_head;
        index_table[index].lines_head = index_table[index].lines_head->next;
        free(temp);
    }
    
    index_table[index].lines_head = NULL;
    for (i = index_table[index].line_count - 1; i >= 0; i--) {
        LineNode *new_node = (LineNode*)malloc(sizeof(LineNode));
        new_node->line_number = lines[i];
        new_node->next = index_table[index].lines_head;
        index_table[index].lines_head = new_node;
    }
    
    free(lines);
}

// In bảng chỉ dẫn
void print_index() {
    printf("\n=== BANG CHI DAN ===\n\n");
    
    for (int i = 0; i < index_count; i++) {
        printf("%-25s ", index_table[i].word);
        
        // Sắp xếp số dòng trước khi in
        sort_line_numbers(i);
        
        LineNode *current = index_table[i].lines_head;
        int first = 1;
        while (current != NULL) {
            if (!first) printf(",");
            printf("%d", current->line_number);
            first = 0;
            current = current->next;
        }
        printf("\n");
    }
}

// Giải phóng bộ nhớ
void cleanup() {
    for (int i = 0; i < index_count; i++) {
        LineNode *current = index_table[i].lines_head;
        while (current != NULL) {
            LineNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main() {
    printf("Chuong trinh tao bang chi dan van ban\n");
    printf("======================================\n\n");
    
    // Đọc stopwords
    load_stopwords("stopw.txt");
    
    // Xử lý văn bản
    process_text("vanban.txt");
    
    printf("Dang sap xep tu...\n");
    // Sắp xếp theo thứ tự từ điển
    qsort(index_table, index_count, sizeof(IndexEntry), compare_entries);
    
    // In kết quả
    print_index();
    
    printf("\nTong so tu trong bang chi dan: %d\n", index_count);
    
    // Giải phóng bộ nhớ
    cleanup();
    
    return 0;
}