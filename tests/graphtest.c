#include <stdio.h>
#include "../graph.h"

void testIsVertextExistSuccessfully();
void testIsVertextExistFailed();
void testIsConnectToSuccessfully();
void testIsConnectToFailed();


int main(){
	testIsVertextExistSuccessfully();
	testIsVertextExistFailed();
	testIsConnectToSuccessfully();
	testIsConnectToFailed();
	return 1;
}

void testIsVertextExistSuccessfully(){
	addVertex(1, NULL);
	addVertex(2, NULL);
	addVertex(3, NULL);
	printf("%d", isVertexExist(1));
	printf("%d", isVertexExist(2));
	printf("%d", isVertexExist(3));

	destroy();
}


void testIsVertextExistFailed(){
	printf("%d", isVertexExist(1));
	printf("%d", isVertexExist(2));
	printf("%d", isVertexExist(3));
}


void testIsConnectToSuccessfully(){
	addVertex(1, NULL);
	addVertex(2, NULL);
	addVertex(3, NULL);
	addEdge(1, 3, '1');
	addEdge(1, 2, '2');
	addEdge(2, 3, '3');
	printf("%d", isConnectTo(1,2));
	printf("%d", isConnectTo(1,3));
	printf("%d", isConnectTo(2,3));

	destroy();
}


void testIsConnectToFailed(){
	addVertex(1, NULL);
	addVertex(2, NULL);
	addEdge(1, 2, '1');
	printf("%d", isConnectTo(1,3));
	printf("%d", isConnectTo(3,2));
	printf("%d", isConnectTo(2,3));

	destroy();
}
