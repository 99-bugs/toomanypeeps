
module.exports = function(grunt) {

    grunt.initConfig({
        watch: {
            sass: {
                files: ['assets/scss/**/*.scss'],
                tasks: ['sass']
            },
            js: {
                files: ['assets/js/**/*.js'],
                tasks: ['concat']
            }
        },
        sass: {
            options: {
                sourceMap: true,
                includePaths: ['bower_components/foundation-sites/scss/']
            },
            dist: {
                files: {
                    'public/css/app.css': 'assets/scss/app.scss'
                }
            }
        },
        concat: {
            dist: {
                src: [
                    'bower_components/jquery/dist/jquery.min.js',
                    'bower_components/foundation-sites/dist/foundation.js',
                    'assets/js/*.js'
                ],
                dest: 'public/js/app.js'
            },
        }
    });

    grunt.loadNpmTasks('grunt-contrib-watch');
    grunt.loadNpmTasks('grunt-sass');
    grunt.loadNpmTasks('grunt-contrib-concat');

    grunt.registerTask('assets', ['sass', 'concat']);
    grunt.registerTask('watch', ['assets', 'watch']);
    grunt.registerTask('default', ['assets']);
};
