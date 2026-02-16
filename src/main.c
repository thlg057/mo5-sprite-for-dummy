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
// STRUCTURES
// ============================================================================

typedef struct {
    int x;  // Position X en octets
    int y;  // Position Y en pixels
} Position;

typedef struct {
    unsigned char *form;
    unsigned char *color;
    int width_bytes;
    int height;
} Sprite;

// ============================================================================
// FONCTIONS UTILITAIRES
// ============================================================================

/**
 * @brief Limite une valeur entre min et max
 */
static int clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

/**
 * @brief Convertit un caractère en majuscule
 */
static char to_upper(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 32;
    }
    return c;
}

// ============================================================================
// GESTION DES ENTRÉES
// ============================================================================

/**
 * @brief Attend et retourne une touche pressée (en majuscule)
 */
static char wait_for_key(void) {
    char ch;
    do {
        ch = mo5_getchar();
    } while (ch == 0);
    return to_upper(ch);
}

/**
 * @brief Met à jour la position en fonction de la touche pressée
 */
static void update_position_from_key(char key, Position *pos) {
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

/**
 * @brief Limite la position aux bords de l'écran
 */
static void clamp_position(Position *pos, const Sprite *sprite) {
    pos->x = clamp(pos->x, 0, SCREEN_WIDTH_BYTES - sprite->width_bytes);
    pos->y = clamp(pos->y, 0, SCREEN_HEIGHT - sprite->height);
}

// ============================================================================
// RENDU
// ============================================================================

/**
 * @brief Dessine un sprite à une position donnée
 */
static void draw_sprite(const Position *pos, const Sprite *sprite) {
    mo5_draw_sprite(pos->x, pos->y, sprite->form, sprite->color,
                    sprite->width_bytes, sprite->height);
}

/**
 * @brief Efface un sprite à une position donnée
 */
static void clear_sprite(const Position *pos, const Sprite *sprite) {
    mo5_clear_sprite(pos->x, pos->y, sprite->width_bytes, sprite->height);
}

// ============================================================================
// BOUCLE PRINCIPALE
// ============================================================================

/**
 * @brief Boucle principale du jeu
 */
static void game_loop(void) {
    Sprite player_sprite;
    Position player_pos;
    Position old_pos;
    char key;

    // Initialisation du sprite du joueur
    player_sprite.form = sprite_perso_form;
    player_sprite.color = sprite_perso_color;
    player_sprite.width_bytes = SPRITE_PERSO_WIDTH_BYTES;
    player_sprite.height = SPRITE_PERSO_HEIGHT;

    // Position initiale (centrée)
    player_pos.x = (SCREEN_WIDTH_BYTES - SPRITE_PERSO_WIDTH_BYTES) / 2;
    player_pos.y = (SCREEN_HEIGHT - SPRITE_PERSO_HEIGHT) / 2;

    // Affichage initial
    draw_sprite(&player_pos, &player_sprite);

    // Boucle de jeu
    while (1) {
        // Sauvegarder l'ancienne position
        old_pos = player_pos;

        // Lire l'entrée utilisateur
        key = wait_for_key();

        // Mettre à jour la position
        update_position_from_key(key, &player_pos);

        // Limiter aux bords de l'écran
        clamp_position(&player_pos, &player_sprite);

        // Redessiner uniquement si la position a changé
        if (player_pos.x != old_pos.x || player_pos.y != old_pos.y) {
            clear_sprite(&old_pos, &player_sprite);
            draw_sprite(&player_pos, &player_sprite);
        }
    }
}

// ============================================================================
// POINT D'ENTRÉE
// ============================================================================

int main(void) {
    // Initialisation du mode graphique
    mo5_init_graphic_mode(COLOR(C_BLACK, C_BLACK));

    // Lancement de la boucle de jeu
    game_loop();

    return 0;
}

