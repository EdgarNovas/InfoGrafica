#include "Model.h"


Model::Model(const std::vector<float>& vertex, const std::vector<float>& uvs, const std::vector<float>& normals) {
	//Calculo la cantidad de vertices que tendre
	this->numvertex = vertex.size() / 3;

	//Generamos el VAO y el VBO
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	//Defino el VAO como activo
	glBindVertexArray(this->VAO);

	//Defino el VBO de las posiciones como activo y paso datos
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(float), vertex.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//Activamos el atributo 0 el VBO 0
	glEnableVertexAttribArray(0);

	//Desvinculo el VAO Y EL VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


}

void Model::Render() const {

	//Vinculo VAO como activo
	glBindVertexArray(this->VAO);

	//Indico cuantos triangulos renderizo
	glDrawArrays(GL_TRIANGLES, 0, this->numvertex);

	//Desvinculo vao
	glBindVertexArray(0);

}