#pragma once
#include "private/defines.h"

namespace rendell {
typedef size_t context_id;

context_id init(const Initer &initer);

class Factory;
void setCurrentFactory(Factory *factory);
Factory *getCurrentFactory();

void release();
void releaseContext(context_id contextId);
void makeCurrent(context_id contextId);
bool swapBuffers();

void setClearBits(uint32_t clearBits);
void clear();
void clearColor(float r, float g, float b, float a);

void setViewport(int x, int y, int width, int height, int windowWidth, int windowHeight);
void setPixelUnpackAlignment(int param);

void startScissors(int x, int y, int width, int height);
void endScissors();

void finish();

void drawLineArrays(uint32_t firstIndex, uint32_t length);
void drawLineArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount);
void drawLineElements(uint32_t count);
void drawLineElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount);

void drawTriangleArrays(uint32_t firstIndex, uint32_t length);
void drawTriangleArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount);
void drawTriangleElements(uint32_t count);
void drawTriangleElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount);

void drawTriangleStripArrays(uint32_t firstIndex, uint32_t length);
void drawTriangleStripArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount);
void drawTriangleStripElements(uint32_t count);
void drawTriangleStripElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount);

} // namespace rendell