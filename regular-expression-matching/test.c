#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define bool int
#define true 1
#define false 0

#define NEW(size, type) (type*)malloc((size)*sizeof(type))
#define NONE_LABEL 256
struct vertex;

typedef struct edge {
    // -128 ~ 127: plain character
    // 256       : empty
    short int label;
    // adjacent state
    struct vertex* vertex;
} Edge;

typedef struct vertex {
    int index;
    Edge* out0;
    Edge* out1;
} Vertex;

Vertex** newNFA (char *s, char* p) {
    Vertex** vertices = NEW(2*strlen(p), Vertex*);
    int i = 0;
    char* t = p;
    while (*t) {
        if (*(t+1) == '*') {
            Vertex* s0 = vertices[i]   = NEW(1, Vertex);
            Vertex* s1 = vertices[i+1] = NEW(1, Vertex);
            Vertex* s2 = vertices[i+2] = NEW(1, Vertex);
            Vertex* s3 = vertices[i+3] = NEW(1, Vertex);

            Edge* e1 = NEW(1, Edge);
            e1->label = NONE_LABEL;
            e1->vertex = s1;
            Edge* e2 = NEW(1, Edge);
            e2->label = NONE_LABEL;
            e2->vertex = s3;
            s0->index = i;
            s0->out0 = e1;
            s0->out1 = e2;

            e1 = NEW(1, Edge);
            e1->label = *t;
            e1->vertex = s2;
            s1->index = i + 1;
            s1->out0 = e1;
            s1->out1 = NULL;

            e1 = NEW(1, Edge);
            e1->label = NONE_LABEL;
            e1->vertex = s1;
            e2 = NEW(1, Edge);
            e2->label = NONE_LABEL;
            e2->vertex = s3;
            s2->index = i + 2;
            s2->out0 = e1;
            s2->out1 = e2;

            s3->index = i + 3;
            s3->out0 = NULL;
            s3->out1 = NULL;
            if (i > 0) {
                Vertex* last = vertices[i-1];
                e1 = NEW(1, Edge);
                e1->label = NONE_LABEL;
                e1->vertex = s0;
                last->out0 = e1;
            }
            i += 4;
        } else {
            Vertex* s0 = vertices[i] = NEW(1, Vertex);
            Vertex* s1 = vertices[i+1] = NEW(1, Vertex);
            Edge* e1 = NEW(1, Edge);
            e1->label = *t;
            e1->vertex = s1;
            s0->index = i;
            s0->out0 = e1;
            s0->out1 = NULL;

            s1->index = i + 1;
            s1->out0 = NULL;
            s1->out1 = NULL;
            if (i > 0) {
                Vertex* last = vertices[i-1];
                e1 = NEW(1, Edge);
                e1->label = NONE_LABEL;
                e1->vertex = s0;
                last->out0 = e1;
            }
            i += 2;
        }
        ++t;
    }
}


int main() {
    char* pattern = "ab*a*c*a";
    Vertex** nfa = newNFA("aaa", pattern);
    int len = 2*(int)strlen(pattern);
    for (int i = 0; i < len; ++i) {
        printf("vertex%d -> ", i);
        Edge* e1 = nfa[i]->out0;
        Edge* e2 = nfa[i]->out1;
        if (e1 != NULL) {
            printf("vertex%d,", e1->vertex->index);
            printf("label: %c,", e1->label != NONE_LABEL ? (char)(e1->label) : '_');
        }
        if (e2 != NULL) {
            printf("vertex%d,", e2->vertex->index);
            printf("label: %c", e2->label != NONE_LABEL ? (char)(e2->label) : '_');
        }
        printf("\n");
    }
    printf("length: %d!\n", len);
    return 0;
}