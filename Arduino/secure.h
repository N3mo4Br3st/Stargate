// ### STRUCTURES ######################

struct ConfReseaux {
  String ssid;
  String pwd;
};

// ### CONSTANTES ######################

int const SIZE_CONFS_RESEAUX(1);
ConfReseaux CONFS_RESEAUX[SIZE_CONFS_RESEAUX];

const struct ConfReseaux ReseauHome;
ReseauHome.ssid = "blablabla";
ReseauHome.pwd = "hoooooooou";

ConfReseaux[0] = ReseauHome;
