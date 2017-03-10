#pragma once

template <typename T>
void filler(T* start, T* end, T value)
{
	for (; start < end; start++)
		*start = value;
}