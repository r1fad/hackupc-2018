# HackUPC 2018: 

## What's this project about?

A productivity tool that helps sofware engineers avoid being pestered.
**Have you ever been in the zone only to have your colleague from HR ask you a pesky question that is totally not urgent?**
This hack would have prevented that by letting everyone know whether you are in the zone and hence unsafe to approach.
On the other hand, it would also tell people when you are slacking off at work. It does all this by looking at 
active process on your machine?

## How was it built?

It took the blood, sweat and tears of three software engineers whose flow gets hampered at work daily. It also uses the 
following things:

1. Arduino Uno
2. 32x32 LED Matrix
3. Electron JS
4. Shell Scripts


## Interacting with the matrix display

The matrix display has 3 states:

- Safe to approach 
![alt text](https://scontent-mad1-1.xx.fbcdn.net/v/t1.15752-9/s2048x2048/44407266_331665574278055_3965596888408784896_n.jpg?_nc_cat=101&_nc_ht=scontent-mad1-1.xx&oh=8c3b233271bf010663f06624201f927b&oe=5C84BA21)

- Do not distrub

![alt text](https://scontent-mad1-1.xx.fbcdn.net/v/t1.15752-9/p2048x2048/44379383_1745253125602930_2259702278631981056_n.jpg?_nc_cat=108&_nc_ht=scontent-mad1-1.xx&oh=a7e071759dca767d2e2f05105efe1556&oe=5C40AE48)

- Go away! ( an animation that lasts a few seconds, telling a person bothering the user to go away)

![alt text](https://scontent-mad1-1.xx.fbcdn.net/v/t1.15752-9/s2048x2048/44442302_313600322795862_6657942239357960192_n.jpg?_nc_cat=108&_nc_ht=scontent-mad1-1.xx&oh=efeb92d04e4554015c22ba5db5ead65e&oe=5C42EC84)


The Arduino listens to Serial for characters, in order to execute commands. You can send the following characters:

- `a` changes state to `Safe to approach`

- `d` changes state to `Do not disturb`

- `g` changes state to start the  `Go away` alert.

- `s`  is to be recieved whenever the user visits [StackOverflow](https://stackoverflow.com/), and increments the bar that is displayed on the `Do not disturb` screen.
