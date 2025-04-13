```markdown
# CSC_5RO05 - Travaux Dirigés

```
```
CSC_5RO05/
├── TD1
├── TD2
├── TD3
└── TD4
```

---

## TD1

### a) **Programme `td1a`**

**Compiler** :
```bash
arm-linux-g++ -Wall -Wextra Timespec.cpp td1a.cpp -o td1a
```

**Exécuter** :
```bash
./td1a
```

---

### b) **Programme `td1b`**

**Compiler** :
```bash
arm-linux-g++ -Wall -Wextra Chrono.cpp Timespec.cpp td1b.cpp -o td1b
```

**Exécuter** :
```bash
./td1b
```

---

## TD2

### a) **Programme `td2a`**

**Compiler** :
```bash
arm-linux-g++ -Wall -Wextra td2a.cpp -o td2a
```

**Exécuter** :
```bash
./td2a
```

---

### b) **Programme `td2b`**

Les éléments publiques sont `Timer()`, `~Timer()`, `start()`, `start_ms()`, `stop()`. Ces méthodes constituent l’interface publique de la classe. Elles permettent aux utilisateurs de créer/détruire le timer, de le configurer et de le contrôler. La visibilité publique garantit l’encapsulation des fonctionnalités principales sans exposer les détails internes (comme `tid`).

Les éléments privés sont `tid` (attribut), car l’identifiant du timer POSIX est un détail d’implémentation qui ne doit pas être manipulé en dehors de la classe, et la méthode `call_callback()`, car cette fonction est une fonction C statique utilisée comme *handler* pour le timer POSIX. Elle est privée car elle sert uniquement au mécanisme interne et ne doit pas être appelée directement.

L’élément protégé est `callback()`, car elle doit forcer son implémentation dans les classes dérivées, tout en évitant qu’elle ne soit appelée depuis l’extérieur de la hiérarchie de classes.

Concernant la déclaration de méthodes comme `const`, dans la classe de base `Timer`, aucun méthode n’a besoin d’être déclarée `const`, car toutes les méthodes publiques (`start()`, `start_ms()`, `stop()`) modifient l’état interne du timer (configuration des durées, arrêt du compteur). La méthode `callback()`, étant purement virtuelle, sera implémentée dans les classes dérivées.

**Compiler** :
```bash
arm-linux-g++ -Wall -Wextra Timer.cpp CountDown.cpp Timespec.cpp td2b.cpp -o td2b
```

**Exécuter** :
```bash
./td2b
```

---

### c) **Programme `td2c`**

Le seul méthode qui peut être déclaré `const` est `getSample()`, car il ne modifie pas l'état interne de l'objet. La méthode `stopLoop()` modifie `doStop`, donc ne peut pas être `const`.

En ce qui concerne la qualification des variables `doStop` et `iLoop`, elles doivent être déclarées comme `volatile` pour garantir que les lectures/écritures ne soient pas optimisées par le compilateur, en particulier dans des contextes multithread. Cela assure que le changement de `doStop` vers `true` soit immédiatement visible lors de l'exécution de la boucle.

**Compiler** :
```bash
arm-linux-g++ -Wall -Wextra Looper.cpp Chrono.cpp Timespec.cpp td2c.cpp -o td2c
```

**Exécuter** :
```bash
./td2c <nLoops>
```

---

### d) **Programme `td2d`**

**Compiler** :
```bash
arm-linux-g++ -Wall -Wextra td2d.cpp Calibrator.cpp Timer.cpp Looper.cpp Chrono.cpp Timespec.cpp -o td2d
```

**Exécuter** :
```bash
./td2d
```

La figure ci-dessous montre la courbe des valeurs de temps d'exécution en fonction des valeurs de `nLoops`, ainsi que la régression linéaire de celle-ci :

!(TD2/td2c.png)

---

### e) **Programme `td2e`**

**Compiler** :
```bash
arm-linux-g++ -Wall -Wextra td2e.cpp CpuLoop.cpp Calibrator.cpp Timer.cpp Looper.cpp Chrono.cpp Timespec.cpp -o td2e
```

**Exécuter** :
```bash
./td2e
```

---

## TD3

### a) **Programmes `td3a`, `td3a2-1t`, `td3a2-3t`, `td3a3`**

**td3a** :
```bash
arm-linux-g++ -Wall -Wextra -pthread td3a.cpp -o td3a
./td3a
```

**td3a2-1t (1 thread)** :
```bash
arm-linux-g++ -Wall -Wextra -pthread td3a2-1t.cpp -o td3a2-1t
./td3a2-1t
```

**td3a2-3t (3 threads)** :
```bash
arm-linux-g++ -Wall -Wextra -pthread td3a2-3t.cpp -o td3a2-3t
./td3a2-3t
```

**td3a3 (avec mutex)** :
```bash
arm-linux-g++ -Wall -Wextra -pthread Incrementer.cpp td3a3.cpp -o td3a3
./td3a3
```

Pour la question 1, après environ 5 secondes, la valeur du compteur est de l'ordre de `1,8e+08`. Ce résultat est obtenu avec une seule tâche incrémentant un compteur local sans partage de données, ce qui permet des incréments très rapides car il n'y a pas de conflit d'accès.

Pour la question 2 avec 3 tâches, la valeur du compteur partagé chute à environ `2,8e+07`. Malgré l'utilisation de trois tâches, la valeur est nettement inférieure à celle obtenue avec une seule tâche partagée (`1,3e+08`). Cela s'explique par les *race conditions* : les accès non synchronisés au compteur provoquent des écrasements de valeurs, réduisant l'efficacité globale. Les trois tâches interfèrent entre elles, entraînant une sous-évaluation du compteur réel.

Pour la question 3 avec `mutex`, la valeur tombe à environ `9,4e+06`. Bien que le `mutex` garantisse un calcul correct du compteur (sans pertes d'incréments), son utilisation introduit un surcoût significatif : l'accès sérialisé au compteur force les tâches à attendre leur tour, ce qui ralentit drastiquement le traitement. La valeur plus faible qu'en question 2 montre que la synchronisation correcte a un impact majeur sur les performances, même si elle élimine les erreurs de concurrence.

---

### d) **Programme `td3d`**

**Compiler** :
```bash
arm-linux-g++ -Wall -Wextra -pthread Counter.cpp Incrementer.cpp Thread.cpp Mutex.cpp TimeoutException.cpp Timespec.cpp td3d.cpp Chrono.cpp -o td3d
```

**Exécuter** :
```bash
./td3d <nLoops> <nTasks> [protect] [policy]
```

**Paramètres** :
- `[protect]` : `true` (activation du mutex) ou `false`.
- `[policy]` : `SCHED_RR`, `SCHED_FIFO`, `SCHED_OTHER`.

Lors des tests avec uniquement les deux premiers paramètres (`nLoops` variant entre 1000 et 10⁸, `nTasks` entre 1 et 5), on observe que l’erreur augmente significativement avec le nombre de tâches. Pour une seule tâche, l’erreur reste nulle, mais dès que `nTasks` dépasse 1, l’erreur devient non négligeable et croît avec `nLoops`. Par exemple, pour `nTasks = 5` et `nLoops = 10⁸`, l’erreur atteint jusqu’à `30 %`, indiquant des accès concurrents non sécurisés au compteur.

Avec le paramètre `protect` activé, l’erreur devient systématiquement `0 %`, quel que soit le nombre de tâches ou d’itérations. Cela confirme que le `mutex` protège efficacement le compteur contre les *race conditions*, garantissant des incréments atomiques.

En utilisant la politique `SCHED_RR`, les résultats restent cohérents (erreur à `0 %` avec `protect`), mais le temps d’exécution augmente notablement pour de grandes valeurs de `nLoops`. Cette surcharge s’explique par la gestion des priorités en temps réel, qui introduit un coût supplémentaire lié à la synchronisation stricte des threads, surtout pour des opérations massives.

---

### e) **Programme `td3e`**

**Compiler** :
```bash
arm-linux-g++ -Wall -Wextra -pthread Thread_A.cpp Thread_B.cpp Thread_C.cpp Thread.cpp Mutex.cpp Chrono.cpp Timespec.cpp Calibrator.cpp CpuLoop.cpp td3e.cpp Looper.cpp Timer.cpp TimeoutException.cpp -o td3e
```

**Exécuter** :
```bash
./td3e <nLoops> <nTasks> [protect] [policy]
```

**Paramètres** :
- `[protect]` : `true` (activation du mutex) ou `false`.
- `[policy]` : `SCHED_RR`, `SCHED_FIFO`, `SCHED_OTHER`.

Lors de la première passe sans protection contre l'inversion de priorité, la tâche A (priorité élevée) est bloquée par la tâche C (priorité basse) qui détient la ressource R, permettant à la tâche B (priorité moyenne) de s'exécuter en profitant de cette inversion, ce qui retarde considérablement l'exécution de A.

En revanche, lors de la deuxième passe avec un `mutex` protégé par héritage de priorité, la priorité de C est temporairement élevée à celle de A dès que A demande R, empêchant B de s'exécuter prématurément. Cela permet à C de libérer R plus rapidement, réduisant ainsi le temps d'attente de A et respectant l'ordre logique des priorités (`A > B > C`).

La protection contre l'inversion supprime donc le risque d'interférence par une tâche intermédiaire, optimisant l'exécution des tâches critiques.

---

## TD4

**Compiler** :
```bash
arm-linux-g++ -Wall -Wextra -pthread Semaphore.cpp TokenProducer.cpp TokenConsumer.cpp Monitor.cpp Mutex.cpp Timespec.cpp Thread.cpp Chrono.cpp TimeoutException.cpp td4.cpp -o td4
```

**Exécuter** :
```bash
./td4 <nConsumers> <nProducers> <tokensPerProducer>
```
