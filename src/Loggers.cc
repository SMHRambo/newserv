#include "Loggers.hh"

#include <phosg/Strings.hh>

using namespace std;

PrefixedLogger ax_messages_log("[$ax message] ", LogLevel::USE_DEFAULT);
PrefixedLogger channel_exceptions_log("[Channel] ", LogLevel::USE_DEFAULT);
PrefixedLogger client_log("", LogLevel::USE_DEFAULT);
PrefixedLogger command_data_log("[Commands] ", LogLevel::USE_DEFAULT);
PrefixedLogger config_log("[Config] ", LogLevel::USE_DEFAULT);
PrefixedLogger dns_server_log("[DNSServer] ", LogLevel::USE_DEFAULT);
PrefixedLogger function_compiler_log("[FunctionCompiler] ", LogLevel::USE_DEFAULT);
PrefixedLogger ip_stack_simulator_log("[IPStackSimulator] ", LogLevel::USE_DEFAULT);
PrefixedLogger license_log("[LicenseManager] ", LogLevel::USE_DEFAULT);
PrefixedLogger lobby_log("", LogLevel::USE_DEFAULT);
PrefixedLogger patch_index_log("[PatchFileIndex] ", LogLevel::USE_DEFAULT);
PrefixedLogger player_data_log("", LogLevel::USE_DEFAULT);
PrefixedLogger proxy_server_log("[ProxyServer] ", LogLevel::USE_DEFAULT);
PrefixedLogger replay_log("[ReplaySession] ", LogLevel::USE_DEFAULT);
PrefixedLogger server_log("[Server] ", LogLevel::USE_DEFAULT);
PrefixedLogger static_game_data_log("[StaticGameData] ", LogLevel::USE_DEFAULT);

static LogLevel log_level_for_name(const string& name) {
  static const unordered_map<string, LogLevel> levels({
      {"debug", LogLevel::DEBUG},
      {"info", LogLevel::INFO},
      {"warning", LogLevel::WARNING},
      {"error", LogLevel::ERROR},
      {"disabled", LogLevel::DISABLED},
  });
  return levels.at(tolower(name));
}

static void set_log_level_from_json(
    PrefixedLogger& log, shared_ptr<JSONObject> d, const char* json_key) {
  try {
    log.min_level = log_level_for_name(d->at(json_key)->as_string());
  } catch (const JSONObject::key_error&) {
  }
}

void set_log_levels_from_json(shared_ptr<JSONObject> json) {
  set_log_level_from_json(ax_messages_log, json, "AXMessages");
  set_log_level_from_json(channel_exceptions_log, json, "ChannelExceptions");
  set_log_level_from_json(client_log, json, "Clients");
  set_log_level_from_json(command_data_log, json, "CommandData");
  set_log_level_from_json(config_log, json, "Config");
  set_log_level_from_json(dns_server_log, json, "DNSServer");
  set_log_level_from_json(function_compiler_log, json, "FunctionCompiler");
  set_log_level_from_json(ip_stack_simulator_log, json, "IPStackSimulator");
  set_log_level_from_json(license_log, json, "LicenseManager");
  set_log_level_from_json(lobby_log, json, "Lobbies");
  set_log_level_from_json(patch_index_log, json, "PatchFileIndex");
  set_log_level_from_json(player_data_log, json, "PlayerData");
  set_log_level_from_json(proxy_server_log, json, "ProxyServer");
  set_log_level_from_json(replay_log, json, "Replay");
  set_log_level_from_json(server_log, json, "GameServer");
  set_log_level_from_json(static_game_data_log, json, "StaticGameData");
}
