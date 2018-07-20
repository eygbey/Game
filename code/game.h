#include "file formats/obj_parser.h"

#define goToEnd(r) returnValue = r; goto end;

s32 returnValue = 1;

void init_application()
{

}

int run_application(ApplicationState* state, GLPlatform platform)
{	

	GLWindow window = create_opengl_context_and_return_maximized_window(platform);

	state->window = window;

	Camera camera = {0};
	V3* camera_pos = &camera.position;
	V3* camera_rot = &camera.rotation;
	camera_pos->x = 0.0f;
	camera_pos->y = 4.0f;
	camera_pos->z = 10.0f;

	V3 orig_camera_pos = *camera_pos;
	V3 orig_camera_rot = *camera_rot;
	
	camera_rot->x = -0.35f;
	camera_rot->y = 0.0f;
	camera_rot->z = 0.0f;

	//Context should be initialized at this point
	oglfunctions_init();
	create_shader_programs();

	u32 window_width 	= window.width;
	u32 window_height 	= window.height;

	get_orthographic_matrix(orthographic_matrix, 0.0f, window_width, 0.0f, window_height, 0.0f, 1.0f);
	get_perspective_matrix(perspective_matrix, 45.0f, window_width / window_height, 0.1f, 1000.0f);

	MeshData test_mesh = {0};

	//load_obj("../res/test_cube.obj", &test_mesh);
	load_obj("../res/manniquin/manniquin.obj", &test_mesh);

	Input* input = &state->input;
	Mouse* mouse = &state->mouse;

	u64* keys = input->keys;

	while(running)
	{
		process_application_inputs(state);
		
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		V3 deltaP = {0};

		if(isKeyDown(keys, I_P)){
			*camera_pos = orig_camera_pos;
			*camera_rot = orig_camera_rot;
		}

		float rot_matrix[14] = {0};
		get_rotation_matrix(rot_matrix, camera.rotation);

		if(isKeyDown(keys, I_W)){
			forward_vector(&deltaP, rot_matrix);
		}
		if(isKeyDown(keys, I_A)){
			left_vector(&deltaP, rot_matrix);	
			deltaP.y = 0.0f;
		}
		if(isKeyDown(keys, I_S)){
			back_vector(&deltaP, rot_matrix);
		}
		if(isKeyDown(keys, I_D)){
			right_vector(&deltaP, rot_matrix);	
			deltaP.y = 0.0f;
		}

		camera_pos->x += deltaP.x * 0.2f;
		camera_pos->y += deltaP.y * 0.2f;
		camera_pos->z += deltaP.z * 0.2f;

		if(isKeyDown(keys, I_LEFT)){
			camera_rot->y += 0.01f;
		}
		if(isKeyDown(keys, I_RIGHT)){
			camera_rot->y -= 0.01f;
		}
		if(isKeyDown(keys, I_UP)){
			camera_rot->x += 0.01f;
		}
		if(isKeyDown(keys, I_DOWN)){
			camera_rot->x -= 0.01f;
		}

		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

		if(isKeyDown(keys, I_Z)){
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		}

		get_view_matrix_from_camera(&camera);


		draw_polygon_single_light(test_mesh.data, test_mesh.size,
							  test_mesh.indices, test_mesh.num_indices,
						      0.0f, 0.0f, 0.0f, 
						      0.502f, 0.502f, 0.502f,
						      test_mesh.uv_offset, test_mesh.n_offset,
						      camera_pos->x, camera_pos->y, camera_pos->z, 
						      1.0f, 1.0f, 1.0f, 1.0f,
						      library_basic_lighting_shader,
						      camera.view, perspective_matrix);

		GLDisplay(window);
	}

end:
	printf("Returning with value: %d\n", returnValue);
	return returnValue;
}