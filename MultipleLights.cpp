#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>

#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "Camera.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"

float vertices[] = {
	-0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f, //
	0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 0.0f, //
	0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f, //
	0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f, //
	-0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 1.0f, //
	-0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f, //

	-0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, //
	0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, //
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, //
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, //
	-0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, //
	-0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, //

	-0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 0.0f, //
	-0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f,  1.0f, 1.0f, //
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f, //
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f, //
	-0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  0.0f, 0.0f, //
	-0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 0.0f, //

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, //
	0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f, //
	0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f, //
	0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f, //
	0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, //
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, //

	-0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f, 1.0f, //
	0.5f,  -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  1.0f, 1.0f, //
	0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f, 0.0f, //
	0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f, 0.0f, //
	-0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  0.0f, 0.0f, //
	-0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f, 1.0f, //

	-0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f, //
	0.5f,  0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 0.0f, //
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f, //
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f, //
	-0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f, //
	-0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f  //
};
glm::vec3 cube_positions[] = {
	glm::vec3(0.0f, 0.0f, 0.0f),     //
	glm::vec3(2.0f, 5.0f, -15.0f),   //
	glm::vec3(-1.5f, -2.2f, -2.5f),  //
	glm::vec3(-3.8f, -2.0f, -12.3f), //
	glm::vec3(2.4f, -0.4f, -3.5f),   //
	glm::vec3(-1.7f, 3.0f, -7.5f),   //
	glm::vec3(1.3f, -2.0f, -2.5f),   //
	glm::vec3(1.5f, 2.0f, -2.5f),    //
	glm::vec3(1.5f, 0.2f, -1.5f),    //
	glm::vec3(-1.3f, 1.0f, -1.5f)    //
};

Camera camera{ glm::vec3(0, 0, 10.0f), 0.0f, 0.0f, glm::vec3(0, 1.0f, 0) };

float x_last, y_last;
bool first_mouse = true;
void MouseCallback(GLFWwindow* window, double x_pos, double y_pos)
{
	if (first_mouse == true)
	{
		x_last = x_pos;
		y_last = y_pos;
		first_mouse = false;
	}

	float x_offset = x_pos - x_last;
	float y_offset = y_pos - y_last;

	x_last = x_pos;
	y_last = y_pos;

	camera.UpdateCameraView(x_offset, y_offset);
	camera.GetViewMatrix();
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.speedZ = -0.03f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.speedZ = 0.03f;
	}
	else
	{
		camera.speedZ = 0.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.speedX = -0.03f;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.speedX = 0.03f;
	}
	else
	{
		camera.speedX = 0.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera.speedY = 0.03f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		camera.speedY = -0.03f;
	}
	else
	{
		camera.speedY = 0.0f;
	}
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, MouseCallback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// 加载glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	VertexBufferObject vbo{ vertices, sizeof(vertices) };
	vbo.Bind();

	VertexArrayObject vao{};
	vao.Bind();
	vao.AddBuffer(0, 3, GL_FLOAT, false, 8 * sizeof(float), 0);
	vao.AddBuffer(1, 3, GL_FLOAT, false, 8 * sizeof(float), 3 * sizeof(float));
	vao.AddBuffer(2, 2, GL_FLOAT, false, 8 * sizeof(float), 6 * sizeof(float));

	Shader shader{ "./shader/MultipleLights.shader" };
	shader.Bind();

	// 纹理
	Texture specular_texture{ "./container2_specular.png", GL_RGBA };
	Texture diffuse_texture{ "./container2.png", GL_RGBA };
	/*
		注意！激活后必须绑定
	*/
	specular_texture.Usetexture(GL_TEXTURE0);
	specular_texture.Bind();
	diffuse_texture.Usetexture(GL_TEXTURE1);
	diffuse_texture.Bind();

	glm::mat4 module_mat = glm::mat4(1.0f);
	glm::mat4 view_mat = glm::mat4(1.0f);
	glm::mat4 project_mat = glm::mat4(1.0f);
	project_mat = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

	// 材质
	float material_ambient[] = { 0.1745f, 0.01175f, 0.01175f };
	unsigned int material_diffuse = diffuse_texture.GetSlot();
	unsigned int  material_speculatr = specular_texture.GetSlot();
	float material_shininess = 64.0f;
	Material material{ material_ambient, material_diffuse , material_speculatr, material_shininess };

	float object_color[3] = { 1.0f, 1.0f, 1.0f };
	float ambient_color[3] = { 0.5f, 0.5f, 0.5f };

	// 所有光源的参数设置
	glm::vec3 light_position = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 light_angles = glm::vec3(glm::radians(-45.0f), glm::radians(-45.0f), glm::radians(0.0f));

	std::vector<glm::vec3> point_light_position = {
		{0.0f, 5.0f, 0.0f},
		{0.0f, 0.0f, 5.0f},
		{5.0f, 0.0f, 0.0f},
	};

	std::vector<glm::vec3> spot_light_position = {
		{0.0f, 10.0f, 0.0f},
		{0.0f, -7.0f, 0.0f},
	};
	std::vector<glm::vec3> spot_light_angles = {
		{glm::radians(0.0f), glm::radians(90.0f), glm::radians(0.0f)},
		{glm::radians(180.0f), glm::radians(0.0f), glm::radians(0.0f)},
	};

	constexpr int POINT_LIGHT_NUMBER = 3;
	constexpr int SPOT_LIGHT_NUMBER = 2;

	// 添加全部灯
	std::vector<glm::vec3> light_cube_position;
	light_cube_position.emplace_back(light_position);
	for (const auto& i : point_light_position)
	{
		light_cube_position.emplace_back(i);
	}
	VertexBufferObject light_VBO{ vertices, sizeof(vertices) };
	VertexArrayObject light_VAO{};
	light_VAO.AddBuffer(2, 3, GL_FLOAT, false, 8 * sizeof(float), 0);
	Shader light_shader("./shader/lightingCube.shader");

	// 平行光
	LightDirectional directional_light{ light_position, light_angles };

	// 点光源
	std::vector<LightPoint> point_light_vector;
	for (int i = 0; i < POINT_LIGHT_NUMBER; i++)
	{
		LightPoint point_light{ point_light_position[i] };
		point_light_vector.emplace_back(point_light);
	}

	// 聚光灯
	std::vector<LightSpot> spot_light_vector;
	for (int i = 0; i < SPOT_LIGHT_NUMBER; i++)
	{
		LightSpot spot_light{ spot_light_position[i], spot_light_angles[i] };
		spot_light_vector.emplace_back(spot_light);
	}

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glEnable(GL_DEPTH_TEST);
		//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ProcessInput(window);
		camera.UpdateCameraPosition();
		view_mat = camera.GetViewMatrix();

		vbo.Bind();
		vao.Bind();
		shader.Bind();
		// 与前文绑定顺序一致
		specular_texture.Bind();
		diffuse_texture.Bind();

		for (int i = 0; i < 10; i++)
		{
			module_mat = glm::mat4(1.0f);
			module_mat = glm::translate(module_mat, cube_positions[i]);
			shader.SetUniformMat4("moduleMat", module_mat);
			shader.SetUniformMat4("viewMat", view_mat);
			shader.SetUniformMat4("projMat", project_mat);

			// 设置材质
			shader.SetUniform1i("material.diffuse", material.m_material_diffuse);
			shader.SetUniform1i("material.specular", material.m_material_specular);
			shader.SetUniform3f("material.ambient", material.m_ambient);
			shader.SetUniform1f("material.shininess", material.m_shininess);

			shader.SetUniform3f("cameraPos", { camera.position.x, camera.position.y, camera.position.z });
			shader.SetUniform3f("objectColor", { 1.0f, 1.0f, 1.0f });
			shader.SetUniform3f("ambientColor", { 0.4f,0.4f,0.4f });

			// 设置平行光
			shader.SetUniform3f("lightD.pos", directional_light.GetPosition());
			shader.SetUniform3f("lightD.color", directional_light.GetColor());
			shader.SetUniform3f("lightD.dirToLight", directional_light.GetDirection());

			// 设置点光源
			for (int i = 0; i < POINT_LIGHT_NUMBER; i++)
			{
				shader.SetUniform3f("lightP[" + std::to_string(i) + "].pos", point_light_vector[i].GetPosition());
				shader.SetUniform3f("lightP[" + std::to_string(i) + "].color", point_light_vector[i].GetColor());
				shader.SetUniform1f("lightP[" + std::to_string(i) + "].constant", point_light_vector[i].constant);
				shader.SetUniform1f("lightP[" + std::to_string(i) + "].linear", point_light_vector[i].linear);
				shader.SetUniform1f("lightP[" + std::to_string(i) + "].quadratic", point_light_vector[i].quadratic);
			}

			// 设置聚光灯
			for (int i = 0; i < SPOT_LIGHT_NUMBER; i++)
			{
				shader.SetUniform3f("lightS[" + std::to_string(i) + "].pos", spot_light_vector[i].GetPosition());
				shader.SetUniform3f("lightS[" + std::to_string(i) + "].color", spot_light_vector[i].GetColor());
				shader.SetUniform3f("lightS[" + std::to_string(i) + "].dirToLight", spot_light_vector[i].GetDirection());
				shader.SetUniform1f("lightS[" + std::to_string(i) + "].constant", spot_light_vector[i].constant);
				shader.SetUniform1f("lightS[" + std::to_string(i) + "].linear", spot_light_vector[i].linear);
				shader.SetUniform1f("lightS[" + std::to_string(i) + "].quadratic", spot_light_vector[i].quadratic);
				shader.SetUniform1f("lightS[" + std::to_string(i) + "].cosPhiOuter", spot_light_vector[i].m_cosPhi);
			}

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}