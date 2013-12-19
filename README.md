sdl-tutorial
============

Este jogo é diferente da outra proposta apresentada para o jogo de
allegro, pois este possui uma perspectiva mais simples e que possa
aproveitar outras formas de recursos para a jogatina.

Conceito de jogo
================

Plataforma 2D
Visão de cima (mas a visão lateral ficaria bastante criativa)
Armadilha

Objetivo
========

O personagem principal tem por objetivo preparar armadilhas para que
os inimigos caiam, assim antes de começar o jogo o mesmo terá o tempo
de 40 segundos para preparar as principais armadilhas antes que os
inimigos entrem no cenário para caça-lo.

O cenário terá três minutos de partida e o estágio só termina quando
os 3 minutos acabarem até lá poderá adquirir pontos quando os inimigos
morrem nas armadilhas colocadas no cenário e estes pontos são convertidos
para que o personagem possa colocar novas armadilhas.

Quando implantar uma armadilha
==============================

No inicio do cenário o personagem principal terá 10 armadilhas que 
poderão ser distribuídas no cenário, após colocar as 10, as cada nova
armadilha dermorará 20 segundos para estar disponível, esse tempo
será reduzido em 10 segundos para cada inimigo que cair em alguma armadilha
no cenário.

Quais tipos de armadilhas
=========================

Bomba:

Destroi no cenário 4 quadrados (pense num tabuleiro de xadrez) de inimigos,
perde au usar

Buraco de estacas de fezes:

Permite que possam cair quantos inimigos
que tentarem passar, permanente no cenário.

Pneu flamejante:

Um pneu que sai rolando no cenário quando um inimigo se
aproximar, pode matar uma fileira de 5 inimigos de uma vez, perde ao usar.

Pombo explosivo:

Pombo mecanico explosivo que vai em direção a inimigos

Armadilha de urso:

Pode ser ocultado no cenário.

Quais tipos de inimigos
=======================

Monstros voadores

Imunes a armadilhas a nível de solo, precisando de armadilhas
que são armas anti aereas.

Zumbis

Burros, vão em direção ao personagem, mesmo que exista uma armadilha
no caminho.

Monstros terrestres

Inteligentes, desviam das armadilhas, neste caso precisa engana-los com
armadilhas que possam ser ocultadas.
