#Création de la classe TAS D AIRE
class Tas_d_aire:
    def __init__(self, tableau, d_aire): # Définition du constructeur avec ses paramètres.
        self.d_aire = d_aire # Initialtion du variable du contructeur.
        self.tableau = tableau[:] # Les valeurs de la variable seront copiées au tableau.
        self.taille_tableau = len(tableau)
        self.tableau[:0] = [None] # l'indexation du tableau se fait à 1
        self.contruire_d_tas()


    def contruire_d_tas(self):
        # On fait l'implémentation des feuilles(s) en mettant en place les positions suivantes jusqu'à n comme suit:
        # Position: ([(D-N)+2] //  d + 1) à n valeurs
        for j in range((self.taille_tableau + self.d_aire - 2)//self.d_aire, 0, -1):
            self.entasser_d_max(j)


    def entasser_d_max(self, i): 
        # Mise en oeuvre du tableau ainsi que son indice avec la méthode entasser.
        # Des triages et vérications se feront sur le tableau pour déterminer leur appartenance.
        # Une permutation se fera si la condition posée est vrai. 
        max = float("-inf")
        index_max = 0
        for j in self.enfants(i): # Vérification de l'existence de la variable j 
            if self.tableau[j] > max:
                max = self.tableau[j]
                index_max = j
        if index_max != 0 and self.tableau[index_max] > self.tableau[i]: # Vérication de la véracité des conditions suivantes.
            self.tableau[index_max], self.tableau[i] = self.tableau[i], self.tableau[index_max] # Permutation des valeurs du tableau selon leur indexation.
            self.entasser_d_max(index_max)        

    def extraire_max(self):
        # Dans cette méthode, on fera l'extraction de certaines valeurs dans le tableau 
        # Une vérification d'une fonction sera et lancera un alerte à son tour si la condition non respectée.
        # Si la condition reste vrai, une extraction se fera et un réaménagment aura lieu.
        if self.taille_tableau < 1: raise Exception("Valeur inférieur dépassée.")
        maxi = self.tableau[1]
        self.tableau[1] = self.tableau[self.taille_tableau] # Initilisation de la variable à l'indice n
        self.taille_tableau = self.taille_tableau - 1
        self.entasser_d_max(1) 
        return maxi

    def augmenter_cle(self, i, cle):
        # Cette méthode fera la modfication de l'indication du tableau tout en lui attribuant une nouvelle valeur
        # Sa procédure d'exécution nous ramène au boucle d'insertion.
        if cle < self.tableau[i]:
            raise Exception("Nouvelle clé plus petite que la clé actuelle.")
        self.tableau[i] = cle
        pi = self.parent(i)
        while i > 1 and self.tableau[pi] < self.tableau[i]: #Vérification des conditions suivantes.
            self.tableau[i], self.tableau[pi] = self.tableau[pi], self.tableau[i] # Si condition vrai, effectuer la permutation des valeur à l'indice n
            i, pi = pi, self.parent(pi)
        
    def inserer(self, cle):
        # Insertion de valeur dans le tableau et vérifier sa taille tout en prenant en consiération les paramètres 
        self.taille_tableau = self.taille_tableau + 1
        if (self.taille_tableau >= len(self.tableau)):
            self.tableau.append(float("-inf"))
        else: self.tableau[self.taille_tableau] = float("-inf")
        self.augmenter_cle(self.taille_tableau,cle)

    def affiche(self):
        # Affichage du tableau, sa taille et sa capacité
        long = len(self.tableau) -1
        print(f"Taille tableau = {self.taille_tableau}", f"\tCapacité tableau: {long}" )

        for i in range(1,self.taille_tableau+1): 
            print(self.tableau[i], end =",")
        print("\n")

    def parent(self,i):#cette méthode nous retourne l'indice du parent de l'enfant à l'indice i 
       x=self.d_aire -2
       return (i + x) // self.d_aire                                  
    def enfants(self, i):#cette méthode nous retourne les indices des enfants du parent à l'indice i 
        return range(self.d_aire * (i-1) + 2, min(self.taille_tableau + 1, self.d_aire * i + 2)) 

# Tests
tableau1 = Tas_d_aire([1,13,3,24,59,68,17,58,99,37,23], 4)

tableau1.affiche()
tableau1.inserer(10.5) # Insertion d'une valeur dans le tableau
tableau1.affiche()

print("les indides des enfants du parent à indice [2]: ", tableau1.enfants(2))
print("l'indice du parent de l'enfant à indice [6]: ", tableau1.parent(6))
print("l'indice du parent de l'enfant à indice [8]: ", tableau1.parent(8))
print("les indides des enfants du parent à indice [4]: ", tableau1.enfants(4))
print("les indides des enfants du parent à indice [3]: ", tableau1.enfants(3))
print("l'indice du parent de l'enfant à indice [9]: ", tableau1.parent(9))
tableau1.affiche() # Affichage du nouveau tableau
tableau1.augmenter_cle(10,4.5) # Ajout de nouvelle valeur à l'indice 6
tableau1.affiche()

tableau1.inserer(.67) # Ajout d'un nouvel élément
tableau1.affiche()
print(tableau1.extraire_max()) # Extraction de la valeur maximale du nouveau tableau.
tableau1.affiche()
print(tableau1.extraire_max())
tableau1.affiche()
tableau1.inserer(255)
tableau1.affiche()
tableau1.augmenter_cle(7,7  )
tableau1.affiche()




