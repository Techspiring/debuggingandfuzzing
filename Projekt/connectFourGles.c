// Copyright 2019 Kevin Mader
// Author: Kevin Mader <mail@kevin-mader.de>

#include <GLES/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "./connectFourGles.h"

GLFWwindow *myWindow;
d2_int32_t windowSize;
uint8_t currentColumn = 0;
uint8_t playerSelection = false;

// In case of a GLFW error, just print an error message to stderr.
static void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

// Close the window when Esc is pressed
static void
key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

static void onMouseMove(GLFWwindow* window, double xpos, double ypos) {
  if (playerSelection)
    return;

  d2_double_t mouse = {0};
  double  column = 0, ppc = 0;
  glfwGetCursorPos(window, &mouse.x, &mouse.y);
  column = mouse.x - (windowSize.x / 2);
  ppc = windowSize.y / 10;

  column /= ppc;
  column += 4.5;
  if (column < 0) column = 0;
  currentColumn = (uint16_t)column;
  if (currentColumn > 7)
    currentColumn = 0;
  return;
}

static void onMouseClick(GLFWwindow* window, int button, int action, int mods) {
  if (playerSelection)
    return;
  if (action != GLFW_RELEASE)
    return;

  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    if (currentColumn) {
      playerSelection = currentColumn;
    }
  } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
    playerSelection = 9;
  }

  return;
}

int8_t initOpenGl(void) {
  // Initialize GLFW
  glfwSetErrorCallback(error_callback);
  if (!glfwInit()) {
    return -1;
  }

  // We want an OpenGL ES 1.1 (or compatible, but I don't think
  // Khronos will ever release OpenGL ES 1.2) context.
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

  // Create a window.
  myWindow = glfwCreateWindow(640, 480,
    "Connect four deluxe", 0, 0);
  if (!myWindow) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(myWindow);

  // Print some information on the OpenGL ES driver
  printf("Renderer: %s\n", glGetString(GL_RENDERER));
  printf("Version: %s\n", glGetString(GL_VERSION));

  glfwSetKeyCallback(myWindow, key_callback);
  glfwSetMouseButtonCallback(myWindow, onMouseClick);
  glfwSetCursorPosCallback(myWindow, onMouseMove);

  return 1;
}

int8_t destroyOpenGl(void) {
  glfwDestroyWindow(myWindow);
  glfwTerminate();
  return 1;
}

bool glesRenderGame(const game_t *cg) {
    glfwGetFramebufferSize(myWindow, &windowSize.x, &windowSize.y);
    float ratio = (float) windowSize.x / (float) windowSize.y;
    glViewport(0, 0, windowSize.x, windowSize.y);

    // Clear the color buffer (to default black clear color)
    glClear(GL_COLOR_BUFFER_BIT);

    // Use a projection suitable for 2D graphics.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrthof(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glScalef(0.2f, 0.2f, 1.0f);
    glTranslatef(0, -3.5f, 0.0f);

    // No rotation, etc for now.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw vertical lines
    for (int i = -4; i < 4; i++) {
        float line_square[8] = {
        (i + 0.48), (0),
        (i + 0.52), (0),
        (i + 0.48), (6),
        (i + 0.52), (6),
        };

        glColor4f(1, 1, 1, 1);
        glVertexPointer(2, GL_FLOAT, 0, line_square);
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    // Draw horizontal lines
        float line_square[8] = {
        (-3.52), (0),
        (-3.52), (-0.04),
        (3.52), (0),
        (3.52), (-0.04),
        };
    glColor4f(1, 1, 1, 1);
    glVertexPointer(2, GL_FLOAT, 0, line_square);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // Draw stones
    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 6; y++) {
        if (cg->player[0].stones[y] & (0x40 >> x)) {
        // Spieler 1 Stein
        glColor4f(0.75, 0, 0, 1);
        } else if (cg->player[1].stones[y] & (0x40 >> x)) {
        // Spieler 2 Stein
        glColor4f(0, 0, 0.75, 1);
        } else {
            continue;
        }

        float stone[8] = {
            (x-3.48), (y+0.98),
            (x-3.48), (y),
            (x-2.52), (y+0.98),
            (x-2.52), (y),
        };
        glVertexPointer(2, GL_FLOAT, 0, stone);
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }
    }

    // Draw Drop-Arrows
    for (int x = 0; x < 7; x++) {
        if ((cg->player[0].stones[5]|cg->player[1].stones[5])
            & (0x40 >> x)) {
            glColor4f(0.2, 0.2, 0.2, 1);
        } else if (currentColumn == x+1) {
            glColor4f(1, 1, 0, 1);
        } else {
            glColor4f(0, 0.5, 0, 1);
        }

        float stone[8] = {
            (x-3.2), 6.2,
            (x-2.8), 6.2,
            (x-3.0), 6.1,
        };
        glVertexPointer(2, GL_FLOAT, 0, stone);
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
    }

    // Draw current stone to drop
    float stone[8] = {
        (currentColumn-4.48), 7.48,
        (currentColumn-3.52), 7.48,
        (currentColumn-4.48), 6.52,
        (currentColumn-3.52), 6.52,
    };
    if (currentColumn && !playerSelection) {
        if (cg->player_active == 0) {
            glColor4f(0.75, 0, 0, 1);
        } else if (cg->player_active == 1) {
            glColor4f(0, 0, 0.75, 1);
        }
        glVertexPointer(2, GL_FLOAT, 0, stone);
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    // Buffer swap to display the new window content.
    glFlush();
    glfwSwapBuffers(myWindow);

    glfwPollEvents();

    return true;
}

int16_t glesPlayerInput(const game_t *cg, uint16_t x) {
  playerSelection = 0;
  while (playerSelection == 0) {
    if (glfwWindowShouldClose(myWindow))
      return -1;
    cg->renderer(cg);
  }
  return playerSelection-1;
}
