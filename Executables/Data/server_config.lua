server_config = {
	environment = {
		framerate = "30Hz"
    },
    systems = {
		graphics = {
		    id = 0,
		    values = {
				windowTitle = " --- Fight Space - Server --- ",
			    inputFile = "/FightSpace.input",
				resolution = {
				    fullscreen = "false",
				    width = "640",
				    height = "480",
				    viewportWidth = "640",
				    viewportHeight = "480",
				    updateViewport = "true",
				    x = "645",
				    y = "0"
				}
		    }
		},
		transform = {
		    id = 1
		},
		network = {
		    id = 2,
		    values = {
				mode = "Server",
		    	port = "4445",
		    	ipFamily= "IPv4"
		    }
		},
		game = {
		    id = 3

		}
    }
}

return server_config