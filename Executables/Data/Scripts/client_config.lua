local client_config = {
	environment = {
		framerate = "30Hz"
    },
    systems = {
		graphics = {
		    id = 0,
		    values = {
				windowTitle = " --- Fight Space - client --- ",
			    inputFile = "/FightSpace.input",
				resolution = {
				    fullscreen = "false",
				    width = "640",
				    height = "480",
				    viewportWidth = "640",
				    viewportHeight = "480",
				    updateViewport = "true",
				    x = "0",
				    y = "0"
				]
		    }
		},
		transform = {
		    id = 1
		},
		network = {
		    id = 2,
		    values = {
				mode = "Client",
		    	port = "4444",
		    	ipFamily= "IPv4"
		    }
		}
    }
}

return client_config