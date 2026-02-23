/*
 * MIT License
 *
 * Copyright (c) 2026 Thierry Le Got
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <cmoc.h>
#include <mo5_defs.h>
#include <mo5_utils.h>
#include <mo5_sprite.h>
#include "assets/perso.h"

// ============================================================================
// CONSTANTES
// ============================================================================

// Vitesse de déplacement
#define MOVE_SPEED_X        1       // Déplacement horizontal (en octets)
#define MOVE_SPEED_Y        4       // Déplacement vertical (en pixels)

// Touches de contrôle
#define KEY_UP              'Z'
#define KEY_DOWN            'S'
#define KEY_LEFT            'A'
#define KEY_RIGHT           'E'

// ============================================================================
// GESTION DES ENTRÉES
// ============================================================================

/**
 * @brief Calcule la nouvelle position en fonction de la touche pressée
 */
static void update_position_from_key(char key, MO5_Position *pos) {
    switch (key) {
        case KEY_UP:
            pos->y -= MOVE_SPEED_Y;
            break;
        case KEY_DOWN:
            pos->y += MOVE_SPEED_Y;
            break;
        case KEY_LEFT:
            pos->x -= MOVE_SPEED_X;
            break;
        case KEY_RIGHT:
            pos->x += MOVE_SPEED_X;
            break;
    }
}

// ============================================================================
// BOUCLE PRINCIPALE
// ============================================================================

/**
 * @brief Boucle principale du jeu
 */
static void game_loop(void) {
    MO5_Sprite player_sprite = SPRITE_PERSO_INIT;
    MO5_Actor  player;
    char       key;

    // Initialisation de l'acteur joueur
    player.sprite  = &player_sprite;
    player.pos.x   = (SCREEN_WIDTH_BYTES - SPRITE_PERSO_WIDTH_BYTES) / 2;
    player.pos.y   = (SCREEN_HEIGHT      - SPRITE_PERSO_HEIGHT)      / 2;
    player.old_pos = player.pos;    // obligatoire avant le premier move

    // Affichage initial
    mo5_actor_draw(&player);

    // Boucle de jeu
    while (1) {
        // Synchronisation sur le retour de trame (50 Hz)
        mo5_wait_vbl();

        // Lire l'entrée utilisateur
        key = mo5_wait_for_key();

        // Calculer la nouvelle position
        MO5_Position new_pos = player.pos;
        update_position_from_key(key, &new_pos);

        // Limiter aux bords de l'écran avant le déplacement
        new_pos.x = mo5_clamp(new_pos.x, 0, SCREEN_WIDTH_BYTES - player.sprite->width_bytes);
        new_pos.y = mo5_clamp(new_pos.y, 0, SCREEN_HEIGHT      - player.sprite->height);

        // Déplacement optimisé (no-op automatique si position identique)
        mo5_actor_move(&player, new_pos.x, new_pos.y);
    }
}

// ============================================================================
// POINT D'ENTRÉE
// ============================================================================

int main(void) {
    // Initialisation du mode graphique
    mo5_video_init(COLOR(C_BLACK, C_BLACK));

    // Lancement de la boucle de jeu
    game_loop();

    return 0;
}