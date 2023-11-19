#include <GL/glfw3.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int WIDTH;
int HEIGHT;
float ballX, ballY, ballSpeedX, ballSpeedY, ballRadius;
float paddleWidth, paddleHeight, paddleSpeed;
float playerPaddleX, playerPaddleY;
float player2PaddleX, player2PaddleY;
int P1points, P2points;

void initializeVariables() {
    WIDTH = WINDOW_WIDTH;
    HEIGHT = WINDOW_HEIGHT;
    ballX = WIDTH / 2;
    ballY = HEIGHT / 2;
    ballSpeedX = 2;
    ballSpeedY = 2;
    ballRadius = 10;
    paddleWidth = 10;
    paddleHeight = 80;
    paddleSpeed = 3;
    glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
    playerPaddleX = 0;
    playerPaddleY = HEIGHT / 2 - paddleHeight / 2;
    
    player2PaddleX = WIDTH - paddleWidth;
    player2PaddleY = HEIGHT / 2 - paddleHeight / 2;
}

void updateBall() {
    ballX += ballSpeedX;
    ballY += ballSpeedY;

    if (ballY - ballRadius < 0 || ballY + ballRadius > HEIGHT) {
        ballSpeedY = -ballSpeedY;
    }

    // Collision with paddles
    if (ballX - ballRadius < playerPaddleX + paddleWidth && ballY > playerPaddleY && ballY < playerPaddleY + paddleHeight ||
        ballX + ballRadius > player2PaddleX && ballY > player2PaddleY && ballY < player2PaddleY + paddleHeight) {
        ballSpeedX = -ballSpeedX;
    }

    // Reset ball when out of bounds
    if (ballX < 0 || ballX > WIDTH) {
        ballX = WIDTH / 2;
        ballY = HEIGHT / 2;
        ballSpeedX = -ballSpeedX;
    }
    
    if(ballX <= 0){
        P2points +=1;
        printf("P2: %d\n", P2points);
	}else if(ballX >= WIDTH){
        P1points +=1;
        printf("P1: %d\n", P1points);
	}
}

void drawPaddle(float x, float y) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + paddleWidth, y);
    glVertex2f(x + paddleWidth, y + paddleHeight);
    glVertex2f(x, y + paddleHeight);
    glEnd();
}

void drawBall() {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i++) {
        float degInRad = i * 3.14159 / 180;
        glVertex2f(ballX + cos(degInRad) * ballRadius, ballY + sin(degInRad) * ballRadius);
    }
    glEnd();
}

int main() {
	
	initializeServer();
	initializeClient();
	
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Pong", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);

    initializeVariables();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Update
        updateBall();

        // Draw
        drawPaddle(playerPaddleX, playerPaddleY);
        drawPaddle(player2PaddleX, player2PaddleY);
        drawBall();

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && playerPaddleY > 0) {
            playerPaddleY -= paddleSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && playerPaddleY < HEIGHT - paddleHeight) {
            playerPaddleY += paddleSpeed;
        }
        
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && player2PaddleY > 0) {
            player2PaddleY -= paddleSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && player2PaddleY < HEIGHT - paddleHeight) {
            player2PaddleY += paddleSpeed;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

