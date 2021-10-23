#include "catch.hpp"
#include <iostream>

extern "C" {
	#include <philo.h>
}

TEST_CASE("get_time_ms") {

	SECTION("check milliseconds") {

		long long	start_ms;
		long long	check_ms;

		start_ms = get_time_ms();
		usleep(1000000);
		check_ms = get_time_ms();
		std::cout << "Start: " << start_ms << " Check: " << check_ms << " Diff: " << (check_ms - start_ms) << std::endl;
	}
}

TEST_CASE("safe_write_msg") {

	SECTION("check all options") {
		pthread_mutex_t	mutex;
		t_philo			philo;
		t_config		config;

		pthread_mutex_init(&mutex, NULL);
		config.write_lock = mutex;
		config.start_time = get_time_ms();
		philo.config = &config;
		philo.num = 1;
		for (int i = 0; i < 5; i++)
			REQUIRE(safe_write_msg(&philo, (enum e_msg)i) != -1);
	}
}