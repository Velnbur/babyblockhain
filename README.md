# Baby Blockchain 

## Технічне завдання

Суттю проекту є створення блокчейну, що буде історією змін деякого файлу або
каталогу файлів на локальній системі. Список змін буде об’єднуватися у коміти а
коміти у блоки, що і будуть додаватися до блокчейну. Надалі, зрозуміло, що
система дуже схожа на принцип роботи системи контролю версій **Git**.

### Операція

Мінімальною одиницею тут буде поняття `операція`, що поділяється на три види:
`додати стрічку B після рядка n`, `видалити рядок n` та `замінити рядок n на
рядок B`. Декілька таких змін формуються вузлом у коміт, їм же підписуються і
потім сукупність комітів можуть бути додані у блок.

Кожна `транзакція`(по аналогії із криптовалютами) і є комітом, що містить список
`операцій`, підпис та публічний ключ того, хто створив коміт(так як ключ і є
ідентифікатором користувача у системі). `Операція` – це структура, що містить тип
`операції` у вигляді цілого беззнакового числа, `B` - стрічка та `n` - ціле
беззнакове число, що розглядалося вище, і відносний шлях до файлу до якого ця
операція і виконуєтся.

Самі дані будуть зберігатися як текст, де поля `операції` ділятся символом `;`, а
самі операції у коміті символом переводу на наступний рядок у Unix форматі (`\n`).
Всі пробіли поза стрічкою `B` будуть не враховуватися. Відносний шлях має
починатися з `/`.

Таким  чином, коміт буде приймати вигляд:
```text
0;2;/hello.txt;”Add string”
1;2;/hello.txt
2;3;/Documents/doc.txt;”Replace string”
```
 
Де перший рядок – трактується як: додати  стрічку `Add string` після третього
рядка до файлу `hello.txt`. Другий: видалити третє стрічку з того же файлу.
Третій: замінити рядок чотири на стрічку `Replace string` у файлі у `doc.txt`
у директорії `Documents`.

### Транзакція або Commit

`Транзакція` або `комміт` - сукупність `операцій`, опису `комміту`, цілого
числа `nonce`, часу створення транзакції та хешу `ID`, що створюєтся об'єднанням
в текстовому вигляді полів вище і алгоритму **SHA1**.

У текстовому форматі `транзакція` приймає вигляд:

``` text
ID
user_id(public_key)
sign
date
description

operation1
operation2
operation3
```

Першими йдуть два рядки `ID`, `description`, `date` потім пустий рядок і список
всіх операцій. Наприклад, беручи операції з прикладy вище:

``` text
7ef271119e9eebe3d6d88026d9a96cea0c4f622a
68C99D9B5401ACAA389C270730C70A6C8CD8B10881AE35E4226CCF75B9...
24A6E976D7499FB3622437BBBC49EE4A6D3E116E08DE45C72F1DF283D8C9283CCF7B3F25367CA82B
23/08/2001 14:55:02
"First commit"

0;2;/hello.txt;”Add string”
1;2;/hello.txt
2;3;/Documents/doc.txt;”Replace string”
```


## Компіляція

Для компіляції у корні проекту запустіть:
> make build

Це створить потрібні директорії, де `build` - директорія всіх `.o` файлів.


## Для розробників 

Для запуска тестів:
> make tests
