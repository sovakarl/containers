# containers


## Contents

1.1. [Part 1](#part-1-реализация-библиотеки-containersh)  
1.2. [Part 2](#part-2-дополнительно-реализация-библиотеки-containersplush)  
1.3. [Part 3](#part-3-дополнительно-реализация-методов-insert_many)


### Part 1. Реализация библиотеки containers.h

Необходимо реализовать классы библиотеки `containers.h`
Список классов: `list` (список), `map` (словарь), `queue` (очередь), `set` (множество), `stack` (стек), `vector` (вектор).
- Оформить решение в виде заголовочного файла `containers.h`, который включает в себя другие заголовочные файлы с реализациями необходимых контейнеров (`list.h`, `map.h` и т. д.).
- Предусмотри Makefile для тестов написанной библиотеки (с целями clean, test).
- За основу взять классическую реализацию контейнеров.

### Part 2. Дополнительно. Реализация библиотеки containersplus.h

Реализовать функции библиотеки `containersplus.h` (спецификации указаны в соответствующих разделах материалов, см. пункт **«Дополнительные контейнеры»**). \
Список классов, которые нужно реализовать дополнительно: `array` (массив), `multiset` (мультимножество).
- Оформить решение в виде заголовочного файла `containersplus.h`, который включает в себя другие заголовочные файлы с реализациями необходимых контейнеров (`array.h`, `multiset.h`).
- Предусмотри Makefile для тестов написанной библиотеки (с целями clean, test).
- За основу взять классическую реализацию контейнеров

### Part 3. Дополнительно. Реализация методов `insert_many`

Необходимо дополнить классы соответствующими методами согласно таблице:

| Modifiers      | Definition                                      | Containers |
|----------------|-------------------------------------------------| -------------------------------------------|
| `iterator insert_many(const_iterator pos, Args&&... args)`          | Inserts new elements into the container directly before `pos`.  | List, Vector. |
| `void insert_many_back(Args&&... args)`          | Appends new elements to the end of the container.  | List, Vector, Queue, Stack. |
| `void insert_many_front(Args&&... args)`          | Appends new elements to the top of the container.  | List. |
| `vector<std::pair<iterator,bool>> insert_many(Args&&... args)`          | Inserts new elements into the container.  | Map, Set, Multiset. |

