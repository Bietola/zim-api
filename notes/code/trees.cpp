// Restituisce se element si trova dentro all'albero node
template <class T>
int search(BinTree<T>* node, T element) {
    if (node == NULL) {
        return 0;
    }
    else if (element < node->val()) {
        return search(node->left(), element);
    }
    else if (element >= node->val()) {
        return search(node->right(), element);
    }
}

// Somma semplice
int sum(BinTree<int>* node) {
    return node->val() + sum(node->left()) + sum(node->right());
}

// Somme con attraversamento/visita (traversal)
int acc = 0;
int sum(BinTree<int>* node) {
    if (node != NULL) {
        acc += node->val();
        sum(node->left());
        sum(node->right());
    }
}

// Codice che funziona usando puntatori
int sum(BinTree<int>* node, int* acc) {
    if (node != NULL) {
        *acc = *acc + node->val();
        sum(node->left(), acc);
        sum(node->right(), acc);
    }
}

// Visita e' utile perche' e' piu' versatile
// Ad esempio possiamo sommare tutto tranne i multipli di 5
// E far valere i multipli di 3 2 volte nella somma
int sum(BinTree<int>* node, int* acc) {
    if (node != NULL) {
        if (node->val() % 5 != 0) {
            if (node->val() % 3 == 0) {
                *acc = *acc + 2*node->val();
            }
            else {
                *acc = *acc + node->val();
            }
        }
        sum(node->left(), acc);
        sum(node->right(), acc);
    }
}

// Restituisci 1 se esiste un cammino con nodi tutti pari dalla radice, altrimenti 0
// NB. Si traduce nel trovare il primo cammino con nodi tutti pari
int trova_pari(Tree<int>* node) {
    if (node == NULL) {
        return 0;
    }
    else if (node->val() % 2 != 0) {
        return 0;
    }
    /* if (node->left() == NULL && node->right() == NULL) { */
    else if (node->isLeaf() == 1) {
        return 1;
    }
    else {
        return trova_pari(node->left()) || trova_pari(node->right());
    }
}

// Restituisci 1 se esiste un cammino con nodi tutti pari dalla radice, altrimenti 0
// NB. Si traduce nel trovare il primo cammino con nodi tutti pari
void trova_pari(Tree<int>* node, int k, int* count, int level) {
    if (node == NULL) {
        return;
    }
    else if (level > k) {
        return;
    }
    else if (node->val() % 2 == 1) {
        return;
    }
    /* if (node->left() == NULL && node->right() == NULL) { */
    else if (node->isLeaf() == 1) {
        (*count)++;
    }
    else {
        trova_pari(node->left(),  k, count, level + 1);
        trova_pari(node->right(), k, count, level + 1);
    }
}
// NB. Nel main la funzione va chiamata inizializzando per bene i parametri di support (count, level)
int main() {
    int mem = 0;
    trova_pari(t1, 3, &mem, 0); // count punta alla memoria della variabile sopra, level inizia a 0
}

// Metodo senza contatore
template <class Elem>
int contaCammini(GTNode<Elem>* subroot, int k){
    if (subroot == NULL) //caso albero vuoto
        return 0;
    else if (k <= 0)
        //se ho superato il livello k posso interrompere la visita
        return 0;
    else if (subroot->val() %2 == 1) //se il nodo contiene un valore dispari posso interrompere la visita
        return 0;
    else if (subroot->isleaf())
        //per gli if precedenti il valore contenuto è pari, non ho superato il livello k
        return 1;
    //verifico se è foglia
    //è pari, non ho superato il livello k, non è foglia, procedo ricorsivamente
    // else return contaCammini(subroot->left(), k-1) + contaCammini(subroot->right(), k-1);
    else {
        /* int acc = 0; */
        /* for (int i = 0; i < subroot->numOfChildren(); i++) { */
        /*     acc += contaCammini(subroot->children[i], k-1); */
        /* } */
        /* return acc; */
        int acc = 0;
        for (GTNode<Elem>* itr = subroot->leftmost_child(); itr != NULL; itr = itr->right_sibling()) {
            acc += contaCammini(itr, k-1);
        }
        return acc;
    }
}
