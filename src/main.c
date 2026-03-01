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
#include <mo5_sprite_bg.h>
#include "assets/perso.h"

// ============================================================================
// CONSTANTES
// ============================================================================

#define MOVE_SPEED_X        1
#define MOVE_SPEED_Y        4

#define KEY_UP              'Z'
#define KEY_DOWN            'S'
#define KEY_LEFT            'A'
#define KEY_RIGHT           'E'

// ============================================================================
// GESTION DES ENTRÉES
// ============================================================================

/**
 * Calcule la nouvelle position en fonction de la touche pressée.
 * Le clamp est appliqué ici pour éviter l'underflow sur unsigned char
 * (0 - 1 = 255 au lieu d'une valeur négative).
 */
static void update_position_from_key(char key, MO5_Position *pos,
                                     unsigned char max_x, unsigned char max_y) {
    switch (key) {
        case KEY_UP:
            if (pos->y >= MOVE_SPEED_Y)
                pos->y -= MOVE_SPEED_Y;
            else
                pos->y = 0;
            break;
        case KEY_DOWN:
            if (pos->y + MOVE_SPEED_Y <= max_y)
                pos->y += MOVE_SPEED_Y;
            else
                pos->y = max_y;
            break;
        case KEY_LEFT:
            if (pos->x >= MOVE_SPEED_X)
                pos->x -= MOVE_SPEED_X;
            else
                pos->x = 0;
            break;
        case KEY_RIGHT:
            if (pos->x + MOVE_SPEED_X <= max_x)
                pos->x += MOVE_SPEED_X;
            else
                pos->x = max_x;
            break;
    }
}

// ============================================================================
// BOUCLE PRINCIPALE
// ============================================================================

static void game_loop(void) {
    MO5_Sprite    player_sprite = SPRITE_PERSO_INIT;
    MO5_Actor     player;
    char          key;
    unsigned char max_x = SCREEN_WIDTH_BYTES - SPRITE_PERSO_WIDTH_BYTES;
    unsigned char max_y = SCREEN_HEIGHT      - SPRITE_PERSO_HEIGHT;

    player.sprite  = &player_sprite;
    player.pos.x   = max_x / 2;
    player.pos.y   = max_y / 2;
    player.old_pos = player.pos;

    mo5_actor_draw_bg(&player);
    while (1) {
        key = mo5_wait_for_key();
        mo5_wait_vbl();
        MO5_Position new_pos = player.pos;
        update_position_from_key(key, &new_pos, max_x, max_y);
        mo5_actor_move_bg(&player, new_pos.x, new_pos.y);
    }
}

// ============================================================================
// POINT D'ENTRÉE
// ============================================================================

int main(void) {
    mo5_video_init(COLOR(C_BLACK, C_BLUE));
    game_loop();
    return 0;
}