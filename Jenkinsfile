pipeline {
agents { docker { image: 'library/gcc' }}
stages {
	stage('Configure') {
		sh 'cmake "CMakeLists.txt"'		
	}
	stage('Build') {
		sh 'make'
	}
	stage('Package') {
		sh 'gzip -c csvtotex > csvtotex.zip'
		archiveArtifacts artifact: '*.zip'
	}
}
}
