#include <stdio.h>

// Fonction qui échange deux entiers via pointeurs
void echange(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Affiche un tableau d'entiers
void affiche_entiers(int *tab, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

// Affiche un tableau de flottants
void affiche_floats(float *tab, int n) {
    for (int i = 0; i < n; i++) {
        printf("%.2f ", tab[i]);
    }
    printf("\n");
}

#include <stdlib.h>

int *copie(int *tab, int n) {
    int *res = malloc(n * sizeof(int));
    if (res == NULL) return NULL; // sécurité
    for (int i = 0; i < n; i++) {
        res[i] = tab[i];
    }
    return res;
}
float *premiers_termes(float u0, float a, float b, int n) {
    float *res = malloc(n * sizeof(float));
    if (res == NULL) return NULL;
    res[0] = u0;
    for (int i = 1; i < n; i++) {
        res[i] = a * res[i-1] + b;
    }
    return res;
}
#include <stdbool.h>

bool *eratosthene(int n) {
    bool *tab = malloc((n+1) * sizeof(bool));
    for (int i = 0; i <= n; i++) tab[i] = true;
    tab[0] = tab[1] = false;

    for (int i = 2; i <= n; i++) {
        if (tab[i]) {
            for (int j = 2*i; j <= n; j += i) {
                tab[j] = false;
            }
        }
    }
    return tab;
}
int *prochaine_ligne(int *t, int n) {
    int *res = malloc((n+2) * sizeof(int));
    res[0] = res[n+1] = 1;
    for (int i = 1; i <= n; i++) {
        res[i] = t[i-1] + t[i];
    }
    return res;
}

int **triangle_de_pascal(int n) {
    int **T = malloc((n+1) * sizeof(int*));
    T[0] = malloc(sizeof(int));
    T[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        T[i] = prochaine_ligne(T[i-1], i-1);
    }
    return T;
}
#include <time.h>
#include <unistd.h>
#include <locale.h>
#include <wchar.h>

int vehicule(int f) {
    if (rand() % f == 0) return 0;
    else return (rand() % 4) + 1;
}

int *init(int f, int n) {
    int *route = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        route[i] = vehicule(f);
    }
    return route;
}

int *next(int *route, int n, int f) {
    int *new_route = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) new_route[i] = 0;

    for (int i = 1; i < n; i++) {
        if (route[i] != 0) {
            if (new_route[i-1] == 0) new_route[i-1] = route[i];
            else new_route[i] = route[i];
        }
    }
    // arrivée aléatoire
    if (route[n-1] == 0) new_route[n-1] = vehicule(f);

    return new_route;
}

void affiche(int *route, int n) {
    wint_t v[] = {' ', 128663, 128665, 128661, 127949};
    setlocale(LC_ALL, "");
    for (int i = 0; i < n; i++) {
        printf("%lc", v[route[i]]);
    }
    printf("\n");
}

int main() {
    srand(time(0));
    int n = 60, f = 2;
    int *route = init(f, n);

    for (int t = 0; t <= 30; t++) {
        affiche(route, n);
        int *new_route = next(route, n, f);
        free(route);
        route = new_route;
        sleep(1);
    }
    free(route);
    return 0;
}